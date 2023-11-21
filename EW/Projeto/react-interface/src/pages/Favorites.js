import { useState, useEffect } from 'react'
import { Navigate, Link } from 'react-router-dom'
import { Container, Card,Button,Row } from 'react-bootstrap'
import { PaginationControl } from 'react-bootstrap-pagination-control';
import { ToastContainer, toast } from 'react-toastify'
import NavBar from '../components/NavBar'
import Accordions from '../components/Accordions'
import axios from 'axios'
import env from '../config/env'
import jwt_decode from 'jwt-decode'
import Fav_Image from '../heart.png'


function Favorites() {
    const [data, setData] = useState([])
    const [favorites, setFavorites] = useState([])
    const [page, setPage] = useState(1)
    const [recordsNumber, setRecordsNumber] = useState(0)
    const [limit,] = useState(25)
    var decodedToken

    useEffect(() => {
        const fetchData = async () => {
            var favorites = []

            try {
                const response = await axios.get(`${env.authAccessPoint}/${decodedToken.username}/favorites?token=${localStorage.token}`)
                favorites = response.data.favorites
            } catch (error) {
                toast.error('Não foi possível obter a lista de favoritos!', {
                    position: toast.POSITION.TOP_CENTER
                })
            }

            if (favorites.length > 0) {
                var queryString = "?"
                var skip = (page - 1) * limit
                for (var i = 0; i < favorites.length; i++) {
                    queryString += "_id=" + favorites[i]["_id"] + "&"
                }

                try {
                    const response = await axios.get(env.apiAcordaosAccessPoint + queryString + `skip=${skip}&limit=${limit}&token=${localStorage.token}`)
                    setRecordsNumber(favorites.length)
                    setData(response.data)

                    setFavorites(favorites)
                } catch (error) {
                    toast.error('Não foi possível obter a lista de acórdãos!', {
                        position: toast.POSITION.TOP_CENTER
                    })
                }
            }
        }

        fetchData()
    }, [page])


    try {
        decodedToken = jwt_decode(localStorage.getItem('token'))
    }
    catch {
        return (<Navigate to="/login" />)
    }

    const handleChangePage = async (page) => {
        setPage(page)
        window.scrollTo(0, 0)
    }


    return (
        <>
            <ToastContainer />
            <NavBar />
            <Container>
                <hr className="mt-4 mb-4" />
                <Card className='d-flex justify-content-center' style={{ 'boxShadow': '0 0.15rem 1.75rem 0 rgb(33 40 50 / 15%)' }} >
                    <Card.Body>
                        <Container className='mt-4'>
                            {data.length>=1 ?(
                                <div>
                            <Accordions page_type="Fav" data={data} setData={setData} favorites={favorites} setFavorites={setFavorites} token={decodedToken} page="favorites"/>
                            <Container className='d-flex justify-content-center mb-4'>
                                <PaginationControl page={page} between={4} total={recordsNumber} limit={limit} changePage={handleChangePage} ellipsis={1} />
                            </Container>
                            </div>
                            ):(  
                                <div>
                                    <Card className="d-flex justify-content-center mb-3" style={{ "boxShadow": "0 0.15rem 1.75rem 0 rgb(33 40 50 / 15%)","height": "3rem" }}>
                                        <Card.Body>
                                            <div className="d-flex justify-content-center mt-2">Ainda não adicionou acórdãos aos favoritos. </div>
                                        </Card.Body>
                                    </Card>
                                    <div className="d-flex justify-content-center mb-3">
                                            <img src={Fav_Image} alt="Imagem de erro " style={{"width":"200px","height":"auto"}} />
                                    </div>
                                    <div className="d-flex justify-content-center">
                                        <Link to="/"> 
                                            <Button type="button" variant="outline-dark">
                                                Comece já!
                                            </Button>
                                        </Link>
                                    </div>
                                </div>
                            )}
                        </Container>
                    </Card.Body>
                </Card>
            </Container>
        </>
    )
}

export default Favorites