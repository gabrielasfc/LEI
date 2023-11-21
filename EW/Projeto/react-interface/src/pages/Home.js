import { useState, useEffect } from "react"
import { Navigate, useSearchParams } from "react-router-dom"
import { Container, Card, Row, Col } from "react-bootstrap"
import { PaginationControl } from 'react-bootstrap-pagination-control';
import { ToastContainer, toast } from "react-toastify"
import NavBar from "../components/NavBar"
import Accordions from "../components/Accordions"
import Search from "../components/Search"
import axios from "axios"
import env from "../config/env"
import jwt_decode from "jwt-decode"
import Aco_Image from '../acordao.png'

function Home() {
    const [data, setData] = useState([])
    const [favorites, setFavorites] = useState([])
    const [page, setPage] = useState(1)
    const [recordsNumber, setRecordsNumber] = useState(0)
    const [search, setSearch] = useState("?")
    const [onSearch, setOnSearch] = useState(false)
    const [searchParams] = useSearchParams()
    const limit = 25

    useEffect(() => {
        const fetchData = async () => {
            try {
                const response1 = await axios.get(env.apiAcordaosAccessPoint + `/number?token=${localStorage.token}`)
                setRecordsNumber(response1.data)

                var lastID = response1.data, page = 1
                if (searchParams.get('page')) {
                    setPage(searchParams.get('page'))
                    page = searchParams.get('page')
                    lastID = response1.data - ((searchParams.get('page') - 1) * limit)
                }

                if (searchParams.get('search') || searchParams.get('tribunal') || searchParams.get('Relator') || searchParams.get('Data do Acordão') ||
                    searchParams.get('Processo') || searchParams.get('Descritores') || searchParams.get('Votação')) {

                    setOnSearch(true)
                    var search = "?", first = true, list = { search: searchParams.get('search'), tribunal: searchParams.get('tribunal'), Relator: searchParams.get('Relator'), "Data do Acordão": searchParams.get('Data do Acordão'), Processo: searchParams.get('Processo'), Descritores: searchParams.get('Descritores'), "Votação": searchParams.get('Votação') }
                    Object.keys(list).forEach(key => {
                        if (list[key]) {
                            if (first) {
                                search += key + '=' + list[key]
                                first = false
                            }
                            else search += '&' + key + '=' + list[key]
                        }
                    })

                    const skip = (page - 1) * limit;
                    const response2 = await axios.get(env.apiAcordaosAccessPoint + `${search}&skip=${skip}&limit=${limit}&token=${localStorage.token}`)
                    setData(response2.data)
                    setSearch(search)
                }
                else {
                    const response2 = await axios.get(`${env.apiAcordaosAccessPoint}?lastID=${lastID}&limit=${limit}&token=${localStorage.token}`)
                    setData(response2.data)
                    console.log(response2)
                }
            } catch (error) {
                toast.error("Não foi possível obter a lista de acórdãos!", { position: toast.POSITION.TOP_CENTER })
            }
        }

        const fetchFavorites = async () => {
            try {
                const response = await axios.get(`${env.authAccessPoint}/${decodedToken.username}/favorites?token=${localStorage.token}`)
                setFavorites(response.data.favorites);
            } catch (error) {
                toast.error("Não foi possível obter a lista de favoritos!", { position: toast.POSITION.TOP_CENTER })
            }
        }

        fetchData()
        fetchFavorites()
    }, [])

    try {
        var decodedToken = jwt_decode(localStorage.getItem("token"))
    } catch {
        return <Navigate to="/login" />
    }

    const handleChangePage = async (page) => {
        setPage(page);

        try {
            if (!onSearch) {
                const lastID = recordsNumber - ((page - 1) * limit)
                const response = await axios.get(env.apiAcordaosAccessPoint + `?lastID=${lastID}&limit=${limit}&token=${localStorage.token}`);
                setData(response.data);
            }
            else {
                const skip = (page - 1) * limit;
                const response = await axios.get(env.apiAcordaosAccessPoint + `${search}&skip=${skip}&limit=${limit}&token=${localStorage.token}`)
                setData(response.data)
            }
            window.scrollTo(0, 0)
        } catch (error) {
            toast.error("Não foi possível obter a lista de acórdãos!", { position: toast.POSITION.TOP_CENTER })
        }
    }

    const handleSearch = async (event) => {
        event.preventDefault()
        setPage(1)

        if (search === "?") setOnSearch(false)
        else setOnSearch(true)
        try {
            const response1 = await axios.get(
                env.apiAcordaosAccessPoint + `/number${search}&token=${localStorage.token}`
            )
            setRecordsNumber(response1.data)

            const response2 = await axios.get(
                env.apiAcordaosAccessPoint + `${search}&skip=0&limit=${limit}&token=${localStorage.token}`
            )
            setData(response2.data);
        } catch (error) {
            toast.error("Não foi possível obter a lista de acórdãos!", { position: toast.POSITION.TOP_CENTER })
        }
    }


    return (
        <>
            <ToastContainer />
            <NavBar />
            <Container>
                <hr className="mt-4 mb-4" />
                <Row>
                    <Col md={3}>
                        <Card className='d-flex justify-content-center mb-xl-0' style={{ 'boxShadow': '0 0.15rem 1.75rem 0 rgb(33 40 50 / 15%)' }} >
                            <Card.Body className="text-center">
                                <Search setSearch={setSearch} handleSearch={handleSearch} />
                            </Card.Body>
                        </Card>
                    </Col>
                    <Col md={9}>
                        {data.length >= 1 ? (
                            <Card className='d-flex justify-content-center' style={{ 'boxShadow': '0 0.15rem 1.75rem 0 rgb(33 40 50 / 15%)' }} >
                                <Card.Body>
                                    <Container className='mt-4'>
                                        <Accordions data={data} setData={setData} favorites={favorites} setFavorites={setFavorites} token={decodedToken} page={page} search={search}/>
                                        <Container className='d-flex justify-content-center mb-4'>
                                            <PaginationControl page={page} between={4} total={recordsNumber} limit={limit} changePage={handleChangePage} ellipsis={1} />
                                        </Container>
                                    </Container>
                                </Card.Body>
                            </Card>
                        ) : (
                            <Card className='d-flex justify-content-center' style={{ 'boxShadow': '0 0.15rem 1.75rem 0 rgb(33 40 50 / 15%)' }} >
                                <Card className="d-flex justify-content-center mb-3" style={{ "boxShadow": "0 0.15rem 1.75rem 0 rgb(33 40 50 / 15%)", "height": "3rem" }}>
                                    <Card.Body>
                                        <div className="d-flex justify-content-center mt-2">Sem acórdãos disponíveis de momento!</div>
                                    </Card.Body>
                                </Card>
                                <div className="d-flex justify-content-center mb-3">
                                    <img src={Aco_Image} alt="Imagem de erro " style={{"width":"400px","height":"auto"}} />
                                </div>
                            </Card>
                        )}
                    </Col>
                </Row>
            </Container>
        </>
    )
}

export default Home
