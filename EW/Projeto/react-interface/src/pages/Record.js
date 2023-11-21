import { useParams, useSearchParams, Link, useNavigate, Navigate } from "react-router-dom"
import { useState, useEffect, React } from "react"
import Button from "@mui/material/Button"
import { Container, ListGroup, ListGroupItem, Card, Modal, Form } from "react-bootstrap"
import { Button as BootstrapButton } from "react-bootstrap"
import { Pencil, Trash3, Heart, HeartFill, ArrowLeftShort } from "react-bootstrap-icons"
import { ToastContainer, toast } from "react-toastify"
import NavBar from "../components/NavBar"
import NoPage from "../pages/NoPage"
import axios from "axios"
import env from "../config/env"
import jwt_decode from "jwt-decode"

function Record() {
    var params = useParams()
    const navigate = useNavigate()
    const [tribunais, setTribunais] = useState({})
    const [searchParams] = useSearchParams()
    const [record, setRecord] = useState(null)
    const [favorites, setFavorites] = useState([])
    const [showModal, setShowModal] = useState(false)
    const [showModalFav, setShowModalFav] = useState(false)
    const [descricaoFav, setDescricaoFav] = useState(false)
    const [FavItemID, setFavItemID] = useState(null)
    const [deleteItemID, setDeleteItemID] = useState(null)
    const [returnURL, setReturnURL] = useState("")
    const [refresh, setRefresh] = useState("")

    useEffect(() => {
        const fetchData = async () => {
            try {
                const response = await axios.get(`${env.apiAcordaosAccessPoint}/${params.id}?token=${localStorage.token}`)
                if (!response.data.error) setRecord(response.data)
                else setRecord("NoPage")
                console.log(response.data)
            } catch (error) { }

            axios.get(env.apiTribunaisAccessPoint + `?token=${localStorage.token}`)
                .then(response => {
                    response.data.forEach(obj => {
                        tribunais[obj._id] = obj.nome
                    })
                    setRefresh(new Date().toISOString())
                })
                .catch(error => {
                    toast.error("Não foi possível obter a lista de tribunais!", { position: toast.POSITION.TOP_CENTER })
                })
        }

        const fetchFavorites = async () => {
            try {
                const response = await axios.get(`${env.authAccessPoint}/${decodedToken.username}/favorites?token=${localStorage.token}`)
                var dictionary = {};
                for (var i = 0; i < response.data.favorites.length; i++) {
                    var elem = response.data.favorites[i];
                    if ("Descricao" in elem) {
                        dictionary[elem["_id"]] = elem["Descricao"];
                    } else {
                        dictionary[elem["_id"]] = "";
                    }
                }
                setFavorites(dictionary)
            } catch (error) {
                toast.error("Não foi possível obter a lista de favoritos!", {
                    position: toast.POSITION.TOP_CENTER
                })
            }
        }

        const parseParams = async () => {
            var returnPage = searchParams.get('returnPage')
            if (returnPage && returnPage === "favorites") {
                setReturnURL("/favorites")
            }
            else {
                var string = "?", first = true, list = { page: searchParams.get('returnPage'), search: searchParams.get('search'), tribunal: searchParams.get('tribunal'), Relator: searchParams.get('Relator'), "Data do Acordão": searchParams.get('Data do Acordão'), Processo: searchParams.get('Processo'), Descritores: searchParams.get('Descritores'), "Votação": searchParams.get('Votação') }
                Object.keys(list).forEach(key => {
                    if (list[key]) {
                        if (first) {
                            string += key + '=' + list[key]
                            first = false
                        }
                        else string += '&' + key + '=' + list[key]
                    }
                })
                setReturnURL("/" + string)
            }
        }

        fetchData()
        fetchFavorites()
        parseParams()
    }, [])

    try {
        var decodedToken = jwt_decode(localStorage.getItem("token"))
    } catch {
        return <Navigate to="/login" />
    }

    const handleFavorite = async (event, id) => {
        try {
            if (id in favorites) {
                await axios.put(env.authAccessPoint + `/${decodedToken.username}/removeFavorite?token=${localStorage.token}`, { favorites: id });
                setFavorites(current => {
                    const updatedFavorites = { ...current };
                    delete updatedFavorites[id];
                    return updatedFavorites;
                });

                toast.success('O acórdão foi removido da lista de favoritos com sucesso!', { position: toast.POSITION.TOP_CENTER });
            }
            else {
                if (descricaoFav) {
                    await axios.put(env.authAccessPoint + `/${decodedToken.username}/favorites?token=${localStorage.token}`, { favorites: { "_id": id, "Descricao": descricaoFav } })
                    setDescricaoFav(null)
                    favorites[id] = descricaoFav
                }
                else {
                    await axios.put(env.authAccessPoint + `/${decodedToken.username}/favorites?token=${localStorage.token}`, { favorites: { "_id": id } })
                }
                favorites[id] = ""
                handleHideModalFav()

                toast.success('O acórdão foi adicionado à lista de favoritos com sucesso!', { position: toast.POSITION.TOP_CENTER })
            }
        } catch (error) {
            toast.error('Não foi possível adicionar o acórdão à lista de favoritos!', { position: toast.POSITION.TOP_CENTER })
        }

    }


    const handleShowModalFav = (event, id) => {
        setShowModalFav(true)
        setFavItemID(id)
    }


    const handleHideModalFav = (event) => {
        setShowModalFav(false)
        setFavItemID(null)
    }


    const handleShowModal = (event, id) => {
        setDeleteItemID(id)
        setShowModal(true)
    }

    const handleHideModal = () => {
        setShowModal(false)
        setDeleteItemID(null)
    }

    const handleDelete = async (event, id) => {
        try {
            await axios.delete(`${env.apiAcordaosAccessPoint}/${id}/?token=${localStorage.token}`)

            toast.success('O acórdão foi removido com sucesso!', {
                position: toast.POSITION.TOP_CENTER
            })

            navigate('/')
        } catch (error) {
            toast.error('Não foi possível remover o acórdão!', {
                position: toast.POSITION.TOP_CENTER
            })
        }

        handleHideModal()
        setRefresh(new Date().toISOString())
    }


    return (
        <>
            {record && (record === "NoPage" ? (
                <NoPage />
            ) : (
                <div>
                    <ToastContainer />
                    <NavBar />
                    <Container>
                        <hr className="mt-4 mb-4" />
                        <div className="d-flex justify-content-start mb-4">
                            <Link to={returnURL} style={{ "textDecoration": "none", color: "inherit" }}>
                                <Button variant="outline-dark" startIcon={<ArrowLeftShort />}>Voltar atrás</Button>
                            </Link>
                        </div>
                        <Card className='d-flex justify-content-center' style={{ 'boxShadow': '0 0.15rem 1.75rem 0 rgb(33 40 50 / 15%)' }} >
                            <Card.Body>
                                <div className="d-flex justify-content-end mb-4">
                                    {params.id in favorites ? <Button variant="outline-dark" startIcon={<HeartFill />} onClick={(event) => handleFavorite(event, params.id)}>Adicionar aos Favoritos</Button>
                                        : <Button variant="outline-dark" startIcon={<Heart />} onClick={(event) => handleShowModalFav(event, params.id)}>Adicionar aos Favoritos</Button>
                                    }
                                    <>
                                        <Modal show={showModalFav && FavItemID == params.id} onHide={handleHideModalFav}>
                                            <Modal.Header closeButton>
                                                <Modal.Title>Adicionar uma descrição</Modal.Title>
                                            </Modal.Header>

                                            <Form>
                                                <div >
                                                    <Form.Group className="my-3 mx-3">
                                                        <Form.Control type="text" placeholder="Descrição" as="textarea" rows={10} onChange={(e) => { setDescricaoFav(e.target.value) }} />
                                                    </Form.Group>
                                                </div>
                                                <Modal.Footer>
                                                    <BootstrapButton variant="default" onClick={(event) => handleFavorite(event, params.id.toString())}>Adicionar aos Favoritos</BootstrapButton>
                                                    <BootstrapButton variant="danger" onClick={handleHideModalFav}>Cancelar</BootstrapButton>
                                                </Modal.Footer>
                                            </Form>
                                        </Modal>
                                    </>
                                    {decodedToken.level === 100 && (
                                        <>
                                            <Link to={"/edit/" + params.id} style={{ 'textDecoration': 'none', 'color': 'inherit' }}>
                                                <Button variant="outline-dark" startIcon={<Pencil />}>Editar Acórdão</Button>
                                            </Link>
                                            <Button variant="outline-dark" startIcon={<Trash3 />} onClick={(event) => handleShowModal(event, params.id)}>Remover Acórdão</Button>
                                            <Modal show={showModal} onHide={handleHideModal}>
                                                <Modal.Header closeButton>
                                                    <Modal.Title>Confirmação de Remoção</Modal.Title>
                                                </Modal.Header>
                                                <Modal.Body>
                                                    <div className="alert alert-danger">Tem a certeza que pretende remover este acórdão?</div>
                                                </Modal.Body>
                                                <Modal.Footer>
                                                    <BootstrapButton variant="default" onClick={handleHideModal}>Cancelar</BootstrapButton>
                                                    <BootstrapButton variant="danger" onClick={(event) => handleDelete(event, deleteItemID)}>Remover</BootstrapButton>
                                                </Modal.Footer>
                                            </Modal>
                                        </>
                                    )}
                                </div>
                                { /* INFORMAÇÃO PRINCIPAL */}
                                <Container className="my-4 mb-5">
                                    <h4>Informação Principal</h4>
                                    <ListGroup> {[
                                        record.Processo && (
                                            <ListGroupItem><b>Processo: </b>{record.Processo}</ListGroupItem>
                                        ),
                                        record["Data do Acordão"] && (
                                            <ListGroupItem><b>Data: </b>{record["Data do Acordão"]}</ListGroupItem>
                                        ),
                                        record.tribunal && (
                                            <ListGroupItem><b>Tribunal: </b>{tribunais.hasOwnProperty(record.tribunal) ? tribunais[record.tribunal] : record.tribunal}</ListGroupItem>
                                        ),
                                        record.Relator && (
                                            <ListGroupItem><b>Relator: </b>{record.Relator}</ListGroupItem>
                                        ),
                                        record["Área Temática 1"].length !== 0 && (
                                            <ListGroupItem key="area-tematica-1">
                                                <b>Área Temática 1: </b>
                                                <ListGroup className="list-group-flush">
                                                    {record["Área Temática 1"].map((obj) => (
                                                        <ListGroupItem key={obj}>{obj}</ListGroupItem>
                                                    ))}
                                                </ListGroup>
                                            </ListGroupItem>
                                        ),
                                        record["Área Temática 2"].length !== 0 && (
                                            <ListGroupItem>
                                                <b>Área Temática 2: </b>
                                                <ListGroup className="list-group-flush">
                                                    {record["Área Temática 2"].map((obj) => (
                                                        <ListGroupItem key={obj}>{obj}</ListGroupItem>
                                                    ))}
                                                </ListGroup>
                                            </ListGroupItem>
                                        ),
                                        record.Descritores.length !== 0 && (
                                            <ListGroupItem>
                                                <b>Descritores: </b>
                                                <ListGroup className="list-group-flush">
                                                    {record.Descritores.map((obj) => (
                                                        <ListGroupItem key={obj}>{obj}</ListGroupItem>
                                                    ))}
                                                </ListGroup>
                                            </ListGroupItem>
                                        ),
                                        record["Votação"] && (
                                            <ListGroupItem><b>Votação: </b>{record["Votação"]}</ListGroupItem>
                                        ),
                                        record["Decisão"] && (
                                            <ListGroupItem><b>Decisão: </b>{record["Decisão"]}</ListGroupItem>
                                        ),
                                        record["Meio Processual"] && (
                                            <ListGroupItem><b>Meio Processual: </b>{record["Meio Processual"]}</ListGroupItem>
                                        ),
                                        record["Sumário"] && (
                                            <ListGroupItem><b>Sumário: </b>{record["Sumário"]}</ListGroupItem>
                                        ),
                                        record["Decisão Texto Integral"] && (
                                            <ListGroupItem><b>Decisão Texto Integral: </b>{record["Decisão Texto Integral"]}</ListGroupItem>
                                        )

                                    ]}
                                    </ListGroup>
                                </Container>
                                { /* OUTRAS INFORMAÇÕES */}
                                <Container className="my-4">
                                    <h4>Outras Informações</h4>
                                    <ListGroup>
                                        {record && record !== "NoPage" && Object.keys(record).map((key) => {
                                            if (typeof record[key] === "object") {
                                                if (key === "Jurisprudências" || key === "Legislações") {
                                                    return Object.keys(record[key]).map((subKey) => {
                                                        if (subKey !== "_id" && record[key][subKey].length > 0) {
                                                            return (
                                                                <ListGroupItem key={`${key}-${subKey}`}>
                                                                    <b>{subKey}: </b>
                                                                    <ListGroup className="list-group-flush">
                                                                        {record[key][subKey].map((obj) => (
                                                                            <ListGroupItem key={obj}>{obj}</ListGroupItem>
                                                                        ))}
                                                                    </ListGroup>
                                                                </ListGroupItem>
                                                            )
                                                        }
                                                        return null
                                                    })
                                                } else if (key === "Informação Auxiliar") {
                                                    return (
                                                        <Container className="my-4">
                                                            <h4 style={{ 'margin-top': '1.5rem' }}>Informação Auxiliar</h4>
                                                            {Object.keys(record[key]).map((subKey) => {
                                                                if (typeof subKey === Object && record[key][subKey].length > 0) {
                                                                    return (
                                                                        <ListGroupItem key={`${key}-${subKey}`}>
                                                                            <b>{subKey}: </b>
                                                                            <ListGroup className="list-group-flush">
                                                                                {record[key][subKey].map((obj) => (
                                                                                    <ListGroupItem key={obj}>{obj}</ListGroupItem>
                                                                                ))}
                                                                            </ListGroup>
                                                                        </ListGroupItem>
                                                                    )
                                                                } else {
                                                                    return (
                                                                        <ListGroupItem subKey={subKey}>
                                                                            <b>{subKey}: </b>
                                                                            {record[key][subKey]}
                                                                        </ListGroupItem>
                                                                    )
                                                                }
                                                            })}
                                                        </Container>
                                                    )
                                                } else if (record[key].length !== 0) {
                                                    return (
                                                        <ListGroupItem key={key}>
                                                            <b>{key}: </b>
                                                            <ListGroup className="list-group-flush">
                                                                {record[key].map((obj) => (
                                                                    <ListGroupItem key={obj}>{obj}</ListGroupItem>
                                                                ))}
                                                            </ListGroup>
                                                        </ListGroupItem>
                                                    )
                                                }
                                            } else if (record[key] && key !== "_id") {
                                                if (key === "Referência Processo")
                                                    return (
                                                        <ListGroupItem key={key}>
                                                            <b>{key}: </b>
                                                            {record[key]}
                                                        </ListGroupItem>
                                                    )
                                                else
                                                    return (
                                                        <ListGroupItem key={key}>
                                                            <b>{key}: </b>
                                                            {record[key]}
                                                        </ListGroupItem>
                                                    )
                                            }
                                            return null
                                        }).filter((item) => {
                                            const keysDisplayed = [
                                                "Processo",
                                                "Data do Acordão",
                                                "tribunal",
                                                "Relator",
                                                "Área Temática 1",
                                                "Área Temática 2",
                                                "Descritores",
                                                "Votação",
                                                "Decisão",
                                                "Meio Processual",
                                                "Sumário",
                                                "Decisão Texto Integral"
                                            ]
                                            return !keysDisplayed.includes(item?.key)
                                        })}
                                    </ListGroup>
                                </Container>
                            </Card.Body>
                        </Card>
                    </Container>
                </div>
            ))}
        </>
    )
}

export default Record
