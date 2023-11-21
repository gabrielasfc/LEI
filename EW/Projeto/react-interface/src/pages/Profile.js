import React, { useState, useEffect, createRef } from "react"
import { Navigate } from "react-router-dom"
import Button from "@mui/material/Button"
import { Container, Row, Col, Form, Card } from "react-bootstrap"
import { Check, Pencil, Trash3, Upload } from "react-bootstrap-icons"
import { ToastContainer, toast } from "react-toastify"
import NavBar from "../components/NavBar"
import axios from "axios"
import jwt_decode from "jwt-decode"
import env from "../config/env"

function Profile() {
    const [username, setUsername] = useState("")
    const [nome, setNome] = useState("")
    const [apelido, setApelido] = useState("")
    const [email, setEmail] = useState("")
    const [passwordAtual, setPasswordAtual] = useState("")
    const [passwordNova, setPasswordNova] = useState("")
    const [filiacao, setFiliacao] = useState("")
    const [nivel, setNivel] = useState("")
    const [showPasswordInputs, setShowPasswordInputs] = useState(false)
    const [dataRegisto, setDataRegisto] = useState("")
    const [ultimoAcesso, setUltimoAcesso] = useState("")
    const [fileURL, setfileURL] = useState()
    var fileInput = createRef()


    useEffect(() => {
        const fetchData = async () => {
            try {
                var decodedToken = jwt_decode(localStorage.getItem("token"))
            } catch {
                return <Navigate to="/login" />
            }

            try {
                const response = await axios.get(env.authAccessPoint + `/${decodedToken.username}?token=${localStorage.token}`)
                if (response.data) {
                    setUsername(response.data.username)
                    setNome(response.data.name)
                    setApelido(response.data.surname)
                    setEmail(response.data.email)
                    setFiliacao(response.data.filiation)
                    if (response.data.level === 10) setNivel("Consumidor")
                    else if (response.data.level === 20) setNivel("Produtor")
                    else setNivel("Administrador")
                    setDataRegisto(response.data.dateCreated)
                    setUltimoAcesso(response.data.lastAccess)
                    setfileURL(env.authAccessPoint + `/i_${response.data.username}?token=${localStorage.token}`)
                }
            } catch {
                toast.error("Não foi obter as informações do utilizador!", {
                    position: toast.POSITION.TOP_CENTER,
                })
            }
        }

        fetchData()
    }, [])


    const handlePassword = () => {
        setShowPasswordInputs(true)
    }


    const handleSubmit = async (event) => {
        event.preventDefault()

        if (showPasswordInputs) {
            if (passwordAtual != null && passwordNova != null) {
                axios.put(env.authAccessPoint + `/${username}/password?token=${localStorage.token}`, {
                    oldpassword: passwordAtual,
                    newpassword: passwordNova,
                })
                    .then((response) => {
                        toast.success("A password foi alterada com sucesso!", {
                            position: toast.POSITION.TOP_CENTER,
                        })

                        axios.put(env.authAccessPoint + "/" + username + `?token=${localStorage.token}`, {
                            name: nome,
                            surname: apelido,
                            username: username,
                            filiation: filiacao,
                        })
                            .then((response) => {
                                toast.success("As alterações foram efetuadas com sucesso!", {
                                    position: toast.POSITION.TOP_CENTER,
                                })
                            })
                            .catch((error) => {
                                toast.error("Não foi possível efetuar as alterações!", {
                                    position: toast.POSITION.TOP_CENTER,
                                })
                            })
                    })
                    .catch((error) => {
                        toast.error("Não foi possível alterar a password!", {
                            position: toast.POSITION.TOP_CENTER,
                        })
                    })
            }
        } else{
            axios.put(env.authAccessPoint + "/" + username + `?token=${localStorage.token}`, {
                name: nome,
                surname: apelido,
                username: username,
                filiation: filiacao,
            })
                .then((response) => {
                    toast.success("As alterações foram efetuadas com sucesso!", {
                        position: toast.POSITION.TOP_CENTER,
                    })
                })
                .catch((error) => {
                    toast.error("Não foi possível efetuar as alterações!", {
                        position: toast.POSITION.TOP_CENTER,
                    })
                })
        }

        URL.revokeObjectURL(fileURL)
        var data = new FormData()
        data.set("image", fileInput.current.files[0])
        if (!fileURL.match(env.authAccessPoint)) {
            await axios.post(env.authAccessPoint + `/image/${username}?token=${localStorage.token}`, data)
                .then((response) => response.json())
                .catch((error) => {})
        }
    }


    const handleRemoveImage = (event) => {
        if (fileInput.current.value || fileURL){
            fileInput.current.value = null
            URL.revokeObjectURL(fileURL)
            setfileURL("")
        }
        else{
            toast.error("O utilizador ainda não tem nenhuma foto!", {
                position: toast.POSITION.TOP_CENTER,
            })
        }   
    }


    const handlefileInputChange = (e) => {
        const file = e.target.files[0]
        if (file) {
            URL.revokeObjectURL(fileURL)
            setfileURL(URL.createObjectURL(file))
        }
    }


    const handleButtonClick = () => {
        document.getElementById('file-input').click()
    }


    return (
        <>
            <ToastContainer />
            <NavBar />
            <Container>
                <hr className="mt-4 mb-4" />
                <Form onSubmit={handleSubmit}>
                    <Row>
                        <Col md={3}>
                            <Card className="mb-4 mb-xl-0" style={{ 'box-shadow': '0 0.15rem 1.75rem 0 rgb(33 40 50 / 15%)' }}>
                                <Card.Body className="text-center">
                                    <img className="img-account-profile rounded-circle mb-2" alt="" src={fileURL} onError={({ currentTarget }) => {
                                        currentTarget.onerror = null // prevents looping
                                        currentTarget.src = env.authAccessPoint + `/default-image.jpg?token=${localStorage.token}`
                                    }}
                                    style={{"width": "250px", "height": "250px", "objectFit": "cover" }}
                                    />
                                    <Button className="mb-4" variant="outline-dark" startIcon={<Trash3 />} onClick={(e) => handleRemoveImage(e)}>Remover Foto</Button>
                                    <div className="small font-italic text-muted mb-2">Insira um ficheiro JPG or PNG até 5 MB</div>
                                    <input id="file-input" type="file" accept="image/*" style={{ display: 'none' }} onChange={handlefileInputChange} ref={fileInput}/>
                                    <Button variant="outline-dark" startIcon={<Upload/>} onClick={handleButtonClick}>Carregar Foto</Button>
                                </Card.Body>
                            </Card>
                        </Col>

                        <Col md={9}>
                            <Card className="mb-4" style={{ 'box-shadow': '0 0.15rem 1.75rem 0 rgb(33 40 50 / 15%)' }}>
                                <Card.Body>
                                    <Row className="gx-3 mb-3">
                                        <Col md={6}>
                                            <Form.Group className="mb-3">
                                                <Form.Label className="small mb-1">Username</Form.Label>
                                                <Form.Control disabled type="text" placeholder="Username" value={username}/>
                                            </Form.Group>
                                        </Col>
                                        <Col md={6}>
                                            <Form.Group className="mb-3">
                                                <Form.Label className="small mb-1">Email</Form.Label>
                                                <Form.Control disabled type="email" placeholder="Email" value={email}/>
                                            </Form.Group>
                                        </Col>
                                    </Row>

                                    <Row className="gx-3 mb-3">
                                        <Col md={6}>
                                            <Form.Group className="mb-3">
                                                <Form.Label className="small mb-1"> Nome </Form.Label>
                                                <Form.Control type="text" placeholder="Nome" value={nome} onChange={(e) => setNome(e.target.value)}/>
                                            </Form.Group>
                                        </Col>
                                        <Col md={6}>
                                            <Form.Group className="mb-3">
                                                <Form.Label className="small mb-1">Apelido</Form.Label>
                                                <Form.Control type="text" placeholder="Apelido" value={apelido} onChange={(e) => setApelido(e.target.value)}/>
                                            </Form.Group>
                                        </Col>
                                    </Row>

                                    {!showPasswordInputs && (
                                        <Form.Group className="mb-3">
                                            <Form.Label className="small mb-1">Password:</Form.Label>
                                            <div className="d-flex flex-column align-items-start">
                                                <Button variant="outline-dark" startIcon={<Pencil />} onClick={handlePassword}>Editar Password</Button>
                                            </div>
                                        </Form.Group>
                                    )}

                                    {showPasswordInputs && (
                                        <Row className="gx-3 mb-3">
                                            <Col md={6}>
                                                <Form.Group className="mb-3">
                                                    <Form.Label className="small mb-1">Password Atual</Form.Label>
                                                    <Form.Control type="password" placeholder="Password Atual" onChange={(e) => setPasswordAtual(e.target.value)}/>
                                                </Form.Group>
                                            </Col>

                                            <Col md={6}>
                                                <Form.Group className="mb-3">
                                                    <Form.Label className="small mb-1">Nova Password</Form.Label>
                                                    <Form.Control type="password" placeholder="Nova Password" onChange={(e) => setPasswordNova(e.target.value)}/>
                                                </Form.Group>
                                            </Col>
                                        </Row>
                                    )}

                                    <Row className="gx-3 mb-3">
                                        <Col md={6}>
                                            <Form.Group className="mb-3">
                                                <Form.Label className="small mb-1">Filiação</Form.Label>
                                                <Form.Control type="text" placeholder="Filiação" value={filiacao} onChange={(e) => setFiliacao(e.target.value)}/>
                                            </Form.Group>
                                        </Col>
                                        <Col md={6}>
                                            <Form.Group className="mb-3">
                                                <Form.Label className="small mb-1">Nível</Form.Label>
                                                <Form.Control disabled type="text" placeholder="Nível" value={nivel}/>
                                            </Form.Group>
                                        </Col>
                                    </Row>

                                    <Row className="gx-3 mb-3">
                                        <Col md={6}>
                                            <Form.Group className="mb-3">
                                                <Form.Label className="small mb-1">Data de Registo</Form.Label>
                                                <Form.Control disabled type="text" placeholder="Data de Registo" value={dataRegisto}/>
                                            </Form.Group>
                                        </Col>
                                        <Col md={6}>
                                            <Form.Group className="mb-3">
                                                <Form.Label className="small mb-1">Data do Último Acesso</Form.Label>
                                                <Form.Control disabled type="text" placeholder="Último Acesso" value={ultimoAcesso}/>
                                            </Form.Group>
                                        </Col>
                                    </Row>

                                    <div className="d-flex justify-content-end">
                                        <Button type="submit" className="mx-2" variant="outline-dark" startIcon={<Check />}>Salvar Alterações</Button>
                                    </div>

                                </Card.Body>
                            </Card>
                        </Col>
                    </Row>
                </Form>
            </Container>
        </>
    )
}

export default Profile
