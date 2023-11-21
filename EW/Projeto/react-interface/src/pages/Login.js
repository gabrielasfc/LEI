import { Navigate, Link } from "react-router-dom"
import { useState } from "react"
import { Col, Button, Row, Container, Card, Form, FloatingLabel } from "react-bootstrap"
import { Facebook, Google } from "react-bootstrap-icons"
import { ToastContainer, toast } from "react-toastify"
import ParticleLayout from "../components/ParticleLayout"
import axios from "axios"
import env from "../config/env"

function Login() {
    const [username, setUsername] = useState("")
    const [password, setPassword] = useState("")
    const [isSubmitted, setIsSubmitted] = useState(false)

    const handleFacebookAuth = () => {
        window.location.href = env.authAccessPoint + "/login/facebook?returnUrl=" + env.interfaceAccessPoint
    }

    const handleGoogleAuth = () => {
        window.location.href = env.authAccessPoint + "/login/google?returnUrl=" + env.interfaceAccessPoint
    }

    const handleSubmit = (event) => {
        axios.post(env.authAccessPoint + "/login", {
            username: username,
            password: password,
        })
            .then((response) => {
                const token = response.data.token
                localStorage.setItem("token", token)

                setIsSubmitted(true)
            })
            .catch((error) => {
                toast.error("Os dados introduzidos são inválidos!", {
                    position: toast.POSITION.TOP_CENTER
                })
            })

        event.preventDefault()
    }

    const loginForm = (
        <>
            <ToastContainer />
            <ParticleLayout />
            <Container>
                <Row className="vh-100 d-flex align-items-center justify-content-center">
                    <Col md={8} lg={5} xs={8}>
                        <Card className="shadow-lg">
                            <Card.Body>
                                <div className="mb-3 mt-md-4">
                                    <h2 className="fw-bold mb-2">Iniciar Sessão</h2>
                                    <p className=" mb-4">Insira os seus dados para iniciar sessão.</p>

                                    <Form onSubmit={handleSubmit}>
                                        <FloatingLabel className="mb-3 form-outline" label="Username">
                                            <Form.Control required type="text" placeholder="Username" value={username} onChange={(e) => setUsername(e.target.value)} />
                                        </FloatingLabel>

                                        <FloatingLabel className="mb-3 form-outline" label="Password">
                                            <Form.Control required type="password" placeholder="Password" value={password} onChange={(e) => setPassword(e.target.value)} />
                                        </FloatingLabel>

                                        <div className="d-flex justify-content-center">
                                            <Button type="submit" variant="outline-dark">Iniciar Sessão</Button>
                                        </div>

                                    </Form>

                                    <div className="mt-3">
                                        <p className="mb-0  text-center">
                                            Não possui conta? {" "}
                                            <a href="/register" className="text-dark fw-bold">
                                                Registar
                                            </a>
                                        </p>
                                    </div>

                                    <div className='d-flex justify-content-center mt-3'>
                                        <Link><Facebook size={30} color='outline-dark' className='mx-2' onClick={(e) => handleFacebookAuth()} /></Link>
                                        <Link><Google size={30} color='outline-dark' className='mx-2' onClick={(e) => handleGoogleAuth()} /></Link>
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
            {isSubmitted ? <Navigate to="/" /> : loginForm}
        </>
    )
}

export default Login
