import { useEffect, useState } from 'react'
import { Link } from 'react-router-dom'
import { Accordion, ListGroup, ListGroupItem, Modal, Button, Container, Form, Row, Col } from 'react-bootstrap'
import { Eye, Pencil, Trash3, Heart, HeartFill } from 'react-bootstrap-icons'
import { toast } from 'react-toastify'
import axios from 'axios'
import env from '../config/env'


function Accordions({ data, setData, favorites, setFavorites, token, page, search, page_type }) {
    const [tribunais, setTribunais] = useState({})
    const [showModal, setShowModal] = useState(false)
    const [showModalFav, setShowModalFav] = useState(false)
    const [descricaoFav, setDescricaoFav] = useState(false)
    const [FavItemID, setFavItemID] = useState(null)
    const [deleteItemID, setDeleteItemID] = useState(null)
    const [refresh, setRefresh] = useState("")

    useEffect(() => {
        const fetchData = async () => {
            var dictionary = {};
            for (var i = 0; i < favorites.length; i++) {
                var elem = favorites[i];
                if ("Descricao" in elem) {
                    dictionary[elem["_id"]] = elem["Descricao"];
                } else {
                    dictionary[elem["_id"]] = "";
                }
            }
            setFavorites(dictionary)
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

        fetchData()
    }, [])

    const handleShowModalFav = (event, id) => {
        setShowModalFav(true)
        setFavItemID(id)
    }


    const handleHideModalFav = (event) => {
        setShowModalFav(false)
        setFavItemID(null)
    }

    const handleFavorite = async (event, id) => {
        try {
            if (id in favorites) {
                await axios.put(env.authAccessPoint + `/${token.username}/removeFavorite?token=${localStorage.token}`, { favorites: id });
                setFavorites(current => {
                    const updatedFavorites = { ...current };
                    delete updatedFavorites[id];
                    return updatedFavorites;
                });

                toast.success('O acórdão foi removido da lista de favoritos com sucesso!', { position: toast.POSITION.TOP_CENTER });
            }
            else {
                if (descricaoFav) {
                    await axios.put(env.authAccessPoint + `/${token.username}/favorites?token=${localStorage.token}`, { favorites: { "_id": id, "Descricao": descricaoFav } })
                    setDescricaoFav(null)
                    favorites[id] = descricaoFav
                }
                else {
                    await axios.put(env.authAccessPoint + `/${token.username}/favorites?token=${localStorage.token}`, { favorites: { "_id": id } })
                }
                favorites[id] = ""
                handleHideModalFav()

                toast.success('O acórdão foi adicionado à lista de favoritos com sucesso!', { position: toast.POSITION.TOP_CENTER })
            }
        } catch (error) {
            toast.error('Não foi possível adicionar o acórdão à lista de favoritos!', { position: toast.POSITION.TOP_CENTER })
        }

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
            await axios.delete(env.apiAcordaosAccessPoint + `/${id}?token=${localStorage.token}`)

            setData(current => { return current.filter((item) => item._id.toString() !== id) })

            toast.success('O acórdão foi removido com sucesso!', {
                position: toast.POSITION.TOP_CENTER
            })
        } catch (error) {
            toast.error('Não foi possível remover o acórdão!', {
                position: toast.POSITION.TOP_CENTER
            })
        }

        handleHideModal();
        setRefresh(new Date().toISOString())
    }


    return (
        <Accordion className='mb-4'>
            {data.map((obj, index) => {
                return (
                    <Accordion.Item eventKey={index}>
                        <Accordion.Header>
                            <Container><b>Processo: </b>{obj.Processo}</Container>
                            <Container className='d-flex justify-content-end px-3'>
                                <Link to={`/${obj._id}?returnPage=${page}` + (search && search !== "?" ? "&" + search.slice(1) : "")}> <Eye size={20} color='black' className='mx-3' /> </Link>
                                {obj._id.toString() in favorites
                                    ? <Link> <HeartFill size={20} color='black' className='mx-3' onClick={(event) => handleFavorite(event, obj._id.toString())} /> </Link>
                                    : <Link> <Heart size={20} color='black' className='mx-3' onClick={(event) => handleShowModalFav(event, obj._id.toString())} /> </Link>
                                }
                                <>
                                    <Modal show={showModalFav && FavItemID == obj._id} onHide={handleHideModalFav}>
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
                                                <Button variant="default" onClick={(event) => handleFavorite(event, obj._id.toString())}>Adicionar aos Favoritos</Button>
                                                <Button variant="danger" onClick={handleHideModalFav}>Cancelar</Button>
                                            </Modal.Footer>
                                        </Form>
                                    </Modal>
                                </>
                                {token.level === 100 && <Link to={"/edit/" + obj._id}> <Pencil size={20} color='black' className='mx-3' /> </Link>}
                                {token.level === 100 &&
                                    <>
                                        <Link><Trash3 size={20} color='black' className='mx-3' onClick={(event) => handleShowModal(event, obj._id.toString())} /></Link>
                                        <Modal show={showModal && obj._id == deleteItemID} onHide={handleHideModal}>
                                            <Modal.Header closeButton>
                                                <Modal.Title>Confirmação de Remoção</Modal.Title>
                                            </Modal.Header>
                                            <Modal.Body>
                                                <div className="alert alert-danger">Tem a certeza que pretende remover este acórdão?</div>
                                            </Modal.Body>
                                            <Modal.Footer>
                                                <Button variant="default" onClick={handleHideModal}>Cancelar</Button>
                                                <Button variant="danger" onClick={(event) => handleDelete(event, deleteItemID)}>Remover</Button>
                                            </Modal.Footer>
                                        </Modal>
                                    </>
                                }
                            </Container>
                        </Accordion.Header>
                        {page_type !== "Fav" ? (
                            <Accordion.Body>
                                <ListGroup>
                                    <ListGroupItem><b>Data: </b>{obj["Data do Acordão"]}</ListGroupItem>
                                    <ListGroupItem><b>Tribunal: </b>{tribunais.hasOwnProperty(obj.tribunal) ? tribunais[obj.tribunal] : obj.tribunal}</ListGroupItem>
                                    <ListGroupItem><b>Relator: </b>{obj.Relator}</ListGroupItem>
                                    <ListGroupItem><b>Descritores: </b>
                                        <ListGroup className='list-group-flush'>
                                            {obj.Descritores.map((content) => { return (<ListGroupItem>{content}</ListGroupItem>) })}
                                        </ListGroup>
                                    </ListGroupItem>
                                </ListGroup>
                            </Accordion.Body>
                        ) : (
                            <Accordion.Body>
                                <ListGroup>
                                    <ListGroupItem><b>Descrição: </b>{favorites[obj._id]}</ListGroupItem>
                                </ListGroup>
                            </Accordion.Body>
                        )}
                    </Accordion.Item>
                )
            })}
        </Accordion>
    )
}

export default Accordions