import { Navigate } from "react-router-dom"
import { useState, useEffect } from "react"
import { Col, Button, Row, Container, Card, Form, FloatingLabel } from "react-bootstrap"
import { ToastContainer, toast } from "react-toastify"
import ParticleLayout from "../components/ParticleLayout"
import axios from "axios"

var env = require("../config/env")

function Register() {
    const [nome, setNome] = useState("")
    const [apelido, setApelido] = useState("")
    const [email, setEmail] = useState("")
    const [username, setUsername] = useState("")
    const [password, setPassword] = useState("")
    const [filiacao, setFiliacao] = useState("")
    const [nivel, setNivel] = useState(10)
    const [isSubmitted, setIsSubmitted] = useState(false)
    const [emailExists, setEmailExists] = useState(false)
    const [usernameExists, setUsernameExists] = useState(false)

    useEffect(() => {
        if (email) checkAccountExists(1)
        else if (username) checkAccountExists(2)
    }, [email, username])

    const checkAccountExists = (type) => {
        if (type === 1) {
            axios.get(env.authAccessPoint + "/check-email/" + email + `?token=${localStorage.token}`)
                .then((response) => {
                    if (response.data != null) setEmailExists(true)
                    else setEmailExists(false)
                })
                .catch((error) => { })
        } else if (type === 2) {
            axios.get(env.authAccessPoint + "/check-username/" + username + `?token=${localStorage.token}`)
                .then((response) => {
                    if (response.data != null) {
                        console.log(response.data)
                        setUsernameExists(true)
                    }
                    else setUsernameExists(false)
                })
                .catch((error) => { })
        }
    }

    const handleSubmit = (event) => {
        event.preventDefault()

        axios.post(`${env.authAccessPoint}/register?token=${localStorage.token}`, {
            name: nome,
            surname: apelido,
            email: email,
            username: username,
            password: password,
            filiation: filiacao,
            level: nivel
        })
            .then((response) => {
                const token = response.data.token

                if (token != null) {
                    localStorage.setItem("token", token)

                    toast.success("O registo foi efetuado com sucesso!", {
                        position: toast.POSITION.TOP_CENTER
                    })

                    setIsSubmitted(true)
                }
                else {
                    toast.error("Não foi possível efetuar o registo!", {
                        position: toast.POSITION.TOP_CENTER
                    })
                }
            })
            .catch((error) => {
                toast.error("Não foi possível efetuar o registo!", {
                    position: toast.POSITION.TOP_CENTER
                })
            })
    }

    const registerForm = (
        <>
            <ToastContainer />
            <ParticleLayout />
            <Container>
                <Row className="vh-100 d-flex align-items-center justify-content-center">
                    <Col md={8} lg={5} xs={8}>
                        <Card className="shadow-lg">
                            <Card.Body>
                                <div className="mb-3 mt-md-4">
                                    <h2 className="fw-bold mb-2">Registar</h2>
                                    <p className=" mb-4">Insira os seus dados para efetuar o registo.</p>

                                    <Form onSubmit={handleSubmit}>
                                        <FloatingLabel className="mb-3 form-outline" label="Nome">
                                            <Form.Control type="text" placeholder="Nome" value={nome} onChange={(e) => setNome(e.target.value)} />
                                        </FloatingLabel>

                                        <FloatingLabel className="mb-3 form-outline" label="Apelido">
                                            <Form.Control type="text" placeholder="Apelido" value={apelido} onChange={(e) => setApelido(e.target.value)} />
                                        </FloatingLabel>

                                        {emailExists ? (
                                            <FloatingLabel className="mb-3 form-outline" label="Email">
                                                <Form.Control required isInvalid type="email" placeholder="Email" value={email} onChange={(e) => setEmail(e.target.value)} />
                                                <Form.Control.Feedback type="invalid"> Já existe uma conta com esse e-mail! </Form.Control.Feedback>
                                            </FloatingLabel>
                                        ) : (
                                            <FloatingLabel className="mb-3 form-outline" label="Email">
                                                <Form.Control required type="email" placeholder="Email" value={email} onChange={(e) => setEmail(e.target.value)} />
                                            </FloatingLabel>
                                        )}

                                        {usernameExists ? (
                                            <FloatingLabel className="mb-3 form-outline" label="Username">
                                                <Form.Control isInvalid required type="text" placeholder="Username" value={username} onChange={(e) => setUsername(e.target.value)} />
                                                <Form.Control.Feedback type="invalid"> O username já está a ser utilizado! </Form.Control.Feedback>
                                            </FloatingLabel>
                                        ) : (
                                            <FloatingLabel className="mb-3 form-outline" label="Username">
                                                <Form.Control required type="text" placeholder="Username" value={username} onChange={(e) => setUsername(e.target.value)} />
                                            </FloatingLabel>
                                        )}

                                        <FloatingLabel className="mb-3 form-outline" label="Password">
                                            <Form.Control required type="password" placeholder="Password" value={password} onChange={(e) => setPassword(e.target.value)} />
                                        </FloatingLabel>

                                        <FloatingLabel className="mb-3 form-outline" label="Filiação">
                                            <Form.Control type="text" placeholder="Filiação" value={filiacao} onChange={(e) => setFiliacao(e.target.value)} />
                                        </FloatingLabel>

                                        <FloatingLabel className="mb-3 form-outline" label="Nível">
                                            <Form.Select onChange={(e) => setNivel(e.target.value)}>
                                                <option value="10">Consumidor</option>
                                                <option value="20">Produtor</option>
                                            </Form.Select>
                                        </FloatingLabel>

                                        <div className="d-flex justify-content-center">
                                            <Button type="submit" variant="outline-dark">Registar</Button>
                                        </div>
                                    </Form>

                                    <div className="mt-3">
                                        <p className="mb-0  text-center">
                                            Já possui conta? {" "}
                                            <a href="/login" className="text-dark fw-bold">
                                                Login
                                            </a>
                                        </p>
                                    </div>
                                </div>
                            </Card.Body>
                        </Card>
                    </Col>
                </Row>
            </Container>
        </>
    )

    return (
        <>
            {isSubmitted ? <Navigate to="/" /> : registerForm}
        </>
    )
}

export default Register
