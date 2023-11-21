import NavBar from "../components/NavBar"
import NoPage from "../pages/NoPage"
import { useParams, Link, useNavigate } from "react-router-dom"
import { useState, useEffect } from "react"
import { Container, Form, Col, Row, Card } from "react-bootstrap"
import Button from '@mui/material/Button'
import { MultiSelect } from "react-multi-select-component";
import { ToastContainer, toast } from "react-toastify"
import { Check, Trash3, PlusCircle } from 'react-bootstrap-icons'
import axios from "axios"

var env = require("../config/env")

function Edit() {
    var params = useParams()
    const navigate = useNavigate();
    const [tribunais, setTribunais] = useState([])
    const [descritores, setDescritores] = useState([])
    const [form, setForm] = useState(null)

    const [refresh, setRefresh] = useState("")
    const [camposSelecionados, setCamposSelecionados] = useState([])
    const [selectedDescritores, setSelectedDescritores] = useState([])
    const [campos, setCampos] = useState([])
    const [isSelected, setIsSelected] = useState(false)

    useEffect(() => {
        const fetchData = async () => {
            var record = []

            axios.get(env.apiTribunaisAccessPoint + `?token=${localStorage.token}`)
                .then(response => {
                    response.data.forEach(obj => { delete obj.descritores })
                    setTribunais(response.data)
                })
                .catch(error => {
                    toast.error("Não foi possível obter a lista de tribunais!", { position: toast.POSITION.TOP_CENTER })
                })


            axios.get(`${env.apiAcordaosAccessPoint}/${params.id}?token=${localStorage.token}`)
                .then(response => {
                    if (!response.data.error) {
                        var id = response.data["_id"]
                        if ("Legislações" in response.data) {
                            Object.keys(response.data["Legislações"]).forEach(key => {
                                if (response.data["Legislações"][key].length > 0) response.data[key] = response.data["Legislações"][key]
                            })
                            delete response.data["Legislações"]
                        }
                        
                        if ("Jurisprudências" in response.data) {
                            Object.keys(response.data["Jurisprudências"]).forEach(key => {
                                if (response.data["Jurisprudências"][key].length > 0) response.data[key] = response.data["Jurisprudências"][key]
                            })
                            delete response.data["Jurisprudências"]
                        }
                        
                        response.data["_id"] = id
                        record = response.data
                        setForm(response.data)
                        setSelectedDescritores(response.data.Descritores.map(descritor => ({ label: descritor, value: descritor })))

                        axios.get(`${env.apiTribunaisAccessPoint}/${response.data.tribunal}?token=${localStorage.token}`)
                            .then(response1 => {
                                response1.data.descritores.sort()
                                setDescritores(response1.data.descritores.map((descritor) => ({ label: descritor, value: descritor })))
                            })
                            .catch(error => {
                                toast.error("Não foi possível obter a lista de descritores!", { position: toast.POSITION.TOP_CENTER })
                            })
                    }
                    else setForm("NoPage")
                })
                .catch(error => {
                    toast.error("Não foi possível obter a informação do acórdão!", { position: toast.POSITION.TOP_CENTER })
                })


            axios.get(env.apiFieldsAccessPoint + `?token=${localStorage.token}`)
                .then(response => {
                    response.data.sort((a, b) => {
                        let f1 = a.field.toLowerCase(), f2 = b.field.toLowerCase()
                        if (f1 < f2) return -1
                        if (f1 > f2) return 1
                        return 0
                    })

                    Object.keys(record).forEach(key => {
                        response.data.forEach(item => {
                            if (item.field === key) {
                                if (Array.isArray(record[key])) {
                                    if (record[key].length > 0) camposSelecionados.push(item)
                                }
                                else camposSelecionados.push(item)
                            }
                        })
                    })

                    response.data.map(item => {
                        if (!camposSelecionados.includes(item)) campos.push(item)
                    })

                })
                .catch(error => {
                    console.log(error)
                    toast.error("Não foi possível obter a lista de campos adicionais!", { position: toast.POSITION.TOP_CENTER })
                })

        }

        fetchData()
    }, [])


    function convertToISO8601(date) {
        var parts = date.split("/");
        var day = parts[0], month = parts[1], year = parts[2]

        if (day.length === 1) { day = "0" + day }
        if (month.length === 1) { month = "0" + month }

        return year + "-" + month + "-" + day
    }


    const handleTribunal = (e) => {
        form["tribunal"] = e.target.value
        setRefresh(new Date().toISOString())

        axios.get(env.apiTribunaisAccessPoint + "/" + e.target.value + `?token=${localStorage.token}`)
            .then(response => {
                response.data.descritores.sort()
                setDescritores(response.data.descritores.map((descritor) => ({ label: descritor, value: descritor })))
            })
            .catch(error => {
                toast.error("Não foi possível obter a lista de descritores!", { position: toast.POSITION.TOP_CENTER })
            })
    }


    const handleChange = (value, field) => {
        form[field] = value
        setRefresh(new Date().toISOString())
    }


    const handleAddField = () => {
        setIsSelected(true)
    }


    const handleFieldChange = (event) => {
        var campo = campos[event.target.selectedIndex - 1]
        setCamposSelecionados(current => [...current, campo])
        setCampos(current => { return current.filter(i => i.field !== campo.field) })

        if (campo.multiselect === "false") form[campo.field] = ""
        else form[campo.field] = [""]

        setIsSelected(false)
    }


    const handleRemoveFieldSingle = (e, item) => {

        delete form[item.field]
        setCamposSelecionados(current => { return current.filter(i => i.field !== item.field) })
        setCampos(current => [...current, item].sort((a, b) => {
            let f1 = a.field.toLowerCase(), f2 = b.field.toLowerCase()
            if (f1 < f2) return -1
            if (f1 > f2) return 1
            return 0
        }))
    }


    const handleMultiAddField = (e, item) => {
        form[item.field] = [...form[item.field], ""]
        setRefresh(new Date().toISOString())
    }


    const handleChangeFieldMulti = (e, index, field) => {
        form[field][index] = e.target.value
        setRefresh(new Date().toISOString())
    }


    const handleMultiRemoveField = (e, index, item) => {
        form[item.field].splice(index, 1)

        if (form[item.field].length < 1) {
            delete form[item.field]
            setCamposSelecionados(current => { return current.filter(i => i.field !== item.field) })
            setCampos(current => [...current, item].sort((a, b) => {
                let f1 = a.field.toLowerCase(), f2 = b.field.toLowerCase()
                if (f1 < f2) return -1
                if (f1 > f2) return 1
                return 0
            }))
        }

        setRefresh(new Date().toISOString())
    }


    const handleSubmit = (event) => {
        event.preventDefault()
        form["Descritores"] = selectedDescritores.map(obj => obj.label)

        var lesgislacoes = {}, jurisprudencias = {}
        Object.keys(form).forEach(key => {
            if (key === "Legislação Nacional" || key === "Legislação Comunitária" || key === "Legislação Estrangeira") {
                lesgislacoes[key] = form[key]
                delete form[key]
            }
            else if (key === "Jurisprudência Nacional" || key === "Jurisprudência Internacional" || key === "Jurisprudência Estrangeira" ||
                key === "Jurisprudência Constitucional" || key === "Outra Jurisprudência") {
                jurisprudencias[key] = form[key]
                delete form[key]
            }
        })

        if (Object.keys(lesgislacoes).length > 0) form["Legislações"] = lesgislacoes
        if (Object.keys(jurisprudencias).length > 0) form["Jurisprudências"] = jurisprudencias
       
        axios.put(env.apiAcordaosAccessPoint + `/${params.id}?token=${localStorage.token}`, form)
            .then(response => {
                toast.success("O acórdão foi atualizado com sucesso!", { position: toast.POSITION.TOP_CENTER })
                setRefresh(new Date().toISOString())
                navigate("/")
            })
            .catch(error => {
                toast.error("Não foi possível atualizar o acórdão!", { position: toast.POSITION.TOP_CENTER })
            })
    }
    
    return (
        <>
            {form && (form === "NoPage" ? (<NoPage />) :
                (
                    <div>
                        <ToastContainer />
                        <NavBar />
                        <Container>
                            <hr className="mt-4 mb-4" />
                            <Card className='d-flex justify-content-center' style={{ 'box-shadow': '0 0.15rem 1.75rem 0 rgb(33 40 50 / 15%)' }} >
                                <Card.Body>
                                    <Form onSubmit={handleSubmit}>
                                        <Container className="my-4 mb-5">
                                            <h4 className="mb-3">Informação Principal</h4>
                                            <Row className="gx-3 mb-3">
                                                <Col md={6}>
                                                    <Form.Group className="mb-3">
                                                        <Form.Label style={{ marginLeft: '10px' }}>Processo:</Form.Label>
                                                        <Form.Control required type="text" placeholder="Processo" value={form["Processo"]} onChange={(e) => handleChange(e.target.value, "Processo")} />
                                                    </Form.Group>
                                                </Col>
                                                <Col md={6}>
                                                    <Form.Group className="mb-3">
                                                        <Form.Label style={{ marginLeft: '10px' }}>Data do Acordão:</Form.Label>
                                                        <Form.Control required type="date" placeholder="Data do Acórdão" value={convertToISO8601(form["Data do Acordão"])} onChange={(e) => handleChange(convertToISO8601(e.target.value), "Data do Acordão")} />
                                                    </Form.Group>
                                                </Col>
                                            </Row>

                                            <Row className="gx-3 mb-3">
                                                <Col md={6}>
                                                    <Form.Group className="mb-3">
                                                        <Form.Label style={{ marginLeft: '10px' }}>Tribunal:</Form.Label>
                                                        <Form.Select value={form.tribunal} onChange={(e) => handleTribunal(e)}>
                                                            {tribunais.map(tribunal => (
                                                                <option key={tribunal._id} value={tribunal._id}>{tribunal.nome}</option>
                                                            ))}
                                                        </Form.Select>
                                                    </Form.Group>
                                                </Col>
                                                <Col md={6}>
                                                    <Form.Group>
                                                        <Form.Label style={{ marginLeft: '10px' }}>Relator:</Form.Label>
                                                        <Form.Control required type="text" placeholder="Relator" value={form["Relator"]} onChange={(e) => handleChange(e.target.value, "Relator")} />
                                                    </Form.Group>
                                                </Col>
                                            </Row>

                                            <Row className="gx-3 mb-3">
                                                <Form.Group className="mb-3">
                                                    <Form.Label style={{ marginLeft: '10px' }}>Descritores:</Form.Label>
                                                    <MultiSelect options={descritores} value={selectedDescritores} onChange={setSelectedDescritores} labelledBy="Selecionar" />
                                                </Form.Group>
                                            </Row>

                                            <Row className="gx-3 mb-3">
                                                <Col md={6}>
                                                    <Form.Label style={{ marginLeft: '10px' }}>Área Temática 1:</Form.Label>
                                                    {
                                                        form["Área Temática 1"] && form["Área Temática 1"].map((area, index) => (
                                                            <Row className="mb-3" key={index}>
                                                                <Col md={11}>
                                                                    <Form.Group>
                                                                        <Form.Control type="text" placeholder={"Área Temática 1 - " + (index + 1)} value={form["Área Temática 1"][index]} onChange={(e) => handleChangeFieldMulti(e, index, campos.find(item => item.field === "Área Temática 1"))} />
                                                                    </Form.Group>
                                                                </Col>
                                                                <Col md={1} className="d-flex justify-content-start">
                                                                    <Link><Trash3 style={{ marginTop: '0.25cm', marginLeft: '-1em' }} size={20} color="black" onClick={(e) => handleMultiRemoveField(e, index, campos.find(item => item.field === "Área Temática 1"))} /></Link>
                                                                </Col>
                                                            </Row>
                                                        ))
                                                    }
                                                    <Row>
                                                        <div style={{ width: '50%' }}>
                                                            <Button className="mb-3" variant="outline-dark" startIcon={<PlusCircle />} style={{ fontSize: '12px' }} onClick={e => handleMultiAddField(e, campos.find(item => item.field === "Área Temática 1"))}>Adicionar Área Temática</Button>
                                                        </div>
                                                    </Row>
                                                </Col>
                                                <Col md={6}>
                                                    <Form.Label style={{ marginLeft: '10px' }}>Área Temática 2:</Form.Label>
                                                    {
                                                        form["Área Temática 2"] && form["Área Temática 2"].map((area, index) => (
                                                            <Row className="mb-3" key={index}>
                                                                <Col md={11}>
                                                                    <Form.Group>
                                                                        <Form.Control type="text" placeholder={"Área Temática 2 - " + (index + 1)} value={form["Área Temática 2"][index]} onChange={(e) => handleChangeFieldMulti(e, index, campos.find(item => item.field === "Área Temática 2"))} />
                                                                    </Form.Group>
                                                                </Col>
                                                                <Col md={1} className="d-flex justify-content-start">
                                                                    <Link><Trash3 style={{ marginTop: '0.25cm', marginLeft: '-1em' }} size={20} color="black" onClick={(e) => handleMultiRemoveField(e, index, campos.find(item => item.field === "Área Temática 2"))} /></Link>
                                                                </Col>
                                                            </Row>
                                                        ))
                                                    }
                                                    <Row>
                                                        <div style={{ width: '50%' }}>
                                                            <Button className="mb-3" variant="outline-dark" startIcon={<PlusCircle />} style={{ fontSize: '12px' }} onClick={e => handleMultiAddField(e, campos.find(item => item.field === "Área Temática 2"))}>Adicionar Área Temática</Button>
                                                        </div>
                                                    </Row>
                                                </Col>
                                            </Row>

                                            <Row className="gx-3 mb-3">
                                                <Form.Group className="mb-3">
                                                    <Form.Label style={{ marginLeft: '10px' }}>Votação:</Form.Label>
                                                    <Form.Control required type="text" placeholder="Votação" value={form["Votação"]} onChange={(e) => handleChange(e.target.value, "Votação")} />
                                                </Form.Group>
                                            </Row>

                                            <Row className="gx-3 mb-3">
                                                <Form.Group className="mb-3">
                                                    <Form.Label style={{ marginLeft: '10px' }}>Decisão:</Form.Label>
                                                    <Form.Control required type="text" placeholder="Decisão" value={form["Decisão"]} onChange={(e) => handleChange(e.target.value, "Decisão")} />
                                                </Form.Group>
                                            </Row>

                                            <Row className="gx-3 mb-3">
                                                <Form.Group>
                                                    <Form.Label style={{ marginLeft: '10px' }}>Meio Processual:</Form.Label>
                                                    <Form.Control required type="text" placeholder="Meio Processual" value={form["Meio Processual"]} onChange={(e) => handleChange(e.target.value, "Meio Processual")} />
                                                </Form.Group>
                                            </Row>

                                            <Row className="gx-3 mb-3">
                                                <Form.Group className="my-3">
                                                    <Form.Label style={{ marginLeft: '10px' }}>Sumário:</Form.Label>
                                                    <textarea required class="form-control" style={{ height: '200px' }} placeholder="Sumário" value={form["Sumário"]} onChange={(e) => handleChange(e.target.value, "Sumário")} />
                                                </Form.Group>
                                            </Row>

                                            <Row className="gx-3 mb-3">
                                                <Form.Group className="my-3">
                                                    <Form.Label style={{ marginLeft: '10px' }}>Decisão Texto Integral:</Form.Label>
                                                    <textarea required class="form-control" style={{ height: '200px' }} placeholder="Decisão Texto Integral" value={form["Decisão Texto Integral"]} onChange={(e) => handleChange(e.target.value, "Decisão Texto Integral")} />
                                                </Form.Group>
                                            </Row>
                                        </Container>

                                        <Container className="my-4 mb-5">
                                            <h4>Outras Informações</h4>
                                            <Button variant="outline-dark" startIcon={<PlusCircle />} style={{ padding: '0.3rem 0.6rem', fontSize: '12px' }} onClick={handleAddField}>Adicionar Informação</Button>
                                            {isSelected && (
                                                <Form.Select className="my-3" defaultValue="" onChange={(e) => handleFieldChange(e)}>
                                                    <option disabled hidden value="">Campo:</option>
                                                    {campos.map(item => {
                                                        return <option>{item.field}</option>
                                                    })}
                                                </Form.Select>
                                            )}
                                            {camposSelecionados.map(item => {
                                                return (
                                                    item.multiselect === "false"
                                                        ?
                                                        <Row className=" mb-3">
                                                            <Col md={11}>
                                                                <Form.Group className="mt-3">
                                                                    <Form.Label style={{ marginLeft: '10px' }}>{item.field}:</Form.Label>
                                                                    <Form.Control required type="text" placeholder={item.field} value={form[item.field]} onChange={(e) => handleChange(e.target.value, item.field)} />
                                                                </Form.Group>
                                                            </Col>
                                                            <Col md={1} className="d-flex justify-content-start">
                                                                <Link><Trash3 style={{ marginTop: '1.5cm', marginLeft: '-1em' }} size={20} color="black" onClick={e => handleRemoveFieldSingle(e, item)} /></Link>
                                                            </Col>
                                                        </Row>
                                                        :
                                                        <>
                                                            <Row>
                                                                <Form.Group className="mt-3">
                                                                    <Form.Label style={{ marginLeft: '10px' }}>{item.field}:</Form.Label>
                                                                </Form.Group>
                                                                {form[item.field].map((value, index) => {
                                                                    return (
                                                                        <Row className="mb-2">
                                                                            <Col md={11}>
                                                                                <Form.Group>
                                                                                    <Form.Control required type="text" placeholder={item.field + " " + (index + 1)} value={form[item.field][index]} onChange={(e) => handleChangeFieldMulti(e, index, item.field)} />
                                                                                </Form.Group>
                                                                            </Col>
                                                                            <Col md={1} className="d-flex justify-content-start">
                                                                                <Link>
                                                                                    <Trash3 style={{ marginTop: '0.25cm', marginLeft: '-1em' }} size={20} color="black" onClick={e => handleMultiRemoveField(e, index, item)} />
                                                                                </Link>
                                                                            </Col>
                                                                        </Row>
                                                                    );
                                                                })}
                                                            </Row>
                                                            <Row>
                                                                <div className="mb-3 d-flex justify-content-start padding-bottom">
                                                                    <Button className="mx-2" variant="outline-dark" startIcon={<PlusCircle />} style={{ padding: '0.3rem 0.6rem', fontSize: '12px' }} onClick={e => handleMultiAddField(e, item)}>Adicionar {item.field}</Button>
                                                                </div>
                                                            </Row>
                                                        </>
                                                )
                                            })}
                                        </Container>
                                        <div className="mb-3 d-flex justify-content-end padding-bottom">
                                            <Button type="submit" className="mx-2" variant="outline-dark" startIcon={<Check />}>Salvar Alterações</Button>
                                        </div>
                                    </Form>
                                </Card.Body>
                            </Card>
                        </Container>
                    </div>
                ))}
        </>
    )
}

export default Edit
