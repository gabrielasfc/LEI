import Button from '@mui/material/Button'
import { useState, useEffect } from 'react'
import { Link } from "react-router-dom"
import { Container, Form, Card, FloatingLabel, Row, Col } from "react-bootstrap"
import { Search as SearchIcon, PlusCircle, Trash3 } from 'react-bootstrap-icons'
import env from "../config/env"
import axios from "axios"

function Search({ setSearch, handleSearch }) {
    const [tribunais, setTribunais] = useState([])
    const [filters, setFilters] = useState([])
    const [possibleFilters, setPossibleFilters] = useState(["Processo", "Data", "Tribunal", "Relator", "Descritores", "Votação"])
    const [queryString, setQueryString] = useState({})
    const [isSelected, setIsSelected] = useState(false)


    useEffect(() => {
        const fetchData = async () => {
            axios.get(env.apiTribunaisAccessPoint + `?token=${localStorage.token}`)
                .then((response) => {
                    console.log(response.data)
                    setTribunais(response.data)
                })
                .catch((error) => { })
        }

        fetchData()
    }, [])


    function convertFromISO8601(date) {
        var parts = date.split("-")
        var year = parts[0], month = parts[1], day = parts[2]

        return day + "/" + month + "/" + year
    }



    const handleAddFilter = () => {
        setIsSelected(true)
    }


    const handleSelectChange = (item) => {
        queryString[item] = ""
        setPossibleFilters(current => {
            return current.filter(i => i !== item)
        })

        setFilters(current => [...current, item])
        setIsSelected(false)
    }


    const handleSearchChange = (filter) => {
        queryString["search"] = filter

        var string = "?", first = true
        Object.keys(queryString).forEach(key => {
            if (queryString[key] !== "") {
                if (key === "Data") {
                    if (first) {
                        string += "Data do Acordão=" + queryString[key]
                        first = false
                    }
                    else string += "&Data do Acordão=" + queryString[key]
                }
                else if (key == "Tribunal") {
                    if (first) {
                        string += "tribunal=" + queryString[key]
                        first = false
                    }
                    else string += "&tribunal=" + queryString[key]
                }
                else {
                    if (first) {
                        string += key + '=' + queryString[key]
                        first = false
                    }
                    else string += '&' + key + '=' + queryString[key]
                }
            }

        })
        setSearch(string)
    }


    const handleFilterChange = (filter, item) => {
        queryString[item] = filter

        var string = "?", first = true
        Object.keys(queryString).forEach(key => {
            if (queryString[key] !== "") {
                if (key === "Data") {
                    if (first) {
                        string += "Data do Acordão=" + queryString[key]
                        first = false
                    }
                    else string += "&Data do Acordão=" + queryString[key]
                }
                else if (key == "Tribunal") {
                    if (first) {
                        string += "tribunal=" + queryString[key]
                        first = false
                    }
                    else string += "&tribunal=" + queryString[key]
                }
                else {
                    if (first) {
                        string += key + '=' + queryString[key]
                        first = false
                    }
                    else string += '&' + key + '=' + queryString[key]
                }
            }

        })
        setSearch(string)
        console.log(queryString)
    }


    const handleRemoveFilter = (e, item) => {
        if (item in queryString) {
            delete queryString[item]
        }

        var string = "?", first = true
        Object.keys(queryString).forEach(key => {
            if (queryString[key] !== "") {
                if (key === "Data") {
                    if (first) {
                        string += "Data do Acordão=" + queryString[key]
                        first = false
                    }
                    else string += "&Data do Acordão=" + queryString[key]
                }
                else if (key == "Tribunal") {
                    if (first) {
                        string += "tribunal=" + queryString[key]
                        first = false
                    }
                    else string += "&tribunal=" + queryString[key]
                }
                else {
                    if (first) {
                        string += key + '=' + queryString[key]
                        first = false
                    }
                    else string += '&' + key + '=' + queryString[key]
                }
            }

        })

        setSearch(string)
        setPossibleFilters(current => [...current, item])
        setFilters(current => {
            return current.filter(i => i !== item)
        })
    }


    return (
        <Container className="mt-3 mb-4">
            <Form onSubmit={handleSearch}>
                <Form.Control className="d-flex mb-5" type="search" placeholder="Pesquisa livre..." aria-label="Procurar" onChange={(e) => handleSearchChange(e.target.value)} />
                <Card>
                    <Card.Header className="d-flex justify-content-center"><p>Filtros</p></Card.Header>
                    <Card.Body>
                        <Card.Body>
                            <Button variant="outline-dark" startIcon={<PlusCircle />} style={{ padding: '0.3rem 0.6rem', fontSize: '12px' }} onClick={handleAddFilter}>Adicionar Filtro</Button>
                            {isSelected && (
                                <Form.Select className="my-3" defaultValue="" onChange={(e) => handleSelectChange(e.target.value)}>
                                    <option disabled hidden value="">Filtro:</option>
                                    {possibleFilters.map(item => {
                                        return <option>{item}</option>
                                    })}
                                </Form.Select>
                            )}
                            {filters.map(item => {
                                if (item === "Tribunal") {
                                    return (
                                        <Row>
                                            <Col md={10}>
                                                <FloatingLabel className="form-outline" label={item} style={{ transform: 'scale(0.90)' }}>
                                                    <Form.Select onChange={(e) => handleFilterChange(e.target.value, item)}>
                                                        {tribunais.map(tribunal => (
                                                            <option key={tribunal._id} value={tribunal._id}>{tribunal.nome}</option>
                                                        ))}
                                                    </Form.Select>
                                                </FloatingLabel>
                                            </Col>
                                            <Col md={1} className="d-flex justify-content-start">
                                                <Link><Trash3 style={{ marginTop: '2em', marginLeft: '-1em' }} size={20} color="black" onClick={e => handleRemoveFilter(e, item)} /></Link>
                                            </Col>
                                        </Row>
                                    )
                                }
                                else if (item === "Data") {
                                    return (
                                        <Row>
                                            <Col md={10}>
                                                <FloatingLabel className="form-outline" label={item} style={{ transform: 'scale(0.90)' }}>
                                                    <Form.Control type="date" placeholder="Data" onChange={(e) => handleFilterChange(convertFromISO8601(e.target.value), item)} />
                                                </FloatingLabel>
                                            </Col>
                                            <Col md={1} className="d-flex justify-content-start">
                                                <Link><Trash3 style={{ marginTop: '2em', marginLeft: '-1em' }} size={20} color="black" onClick={e => handleRemoveFilter(e, item)} /></Link>
                                            </Col>
                                        </Row>
                                    )
                                }
                                else {
                                    return (
                                        <Row>
                                            <Col md={10}>
                                                <FloatingLabel className="form-outline" label={item} style={{ transform: 'scale(0.90)' }}>
                                                    <Form.Control className="my-3" type="search" placeholder={item} value={queryString[item]} onChange={(e) => handleFilterChange(e.target.value, item)} />
                                                </FloatingLabel>
                                            </Col>
                                            <Col md={1} className="d-flex justify-content-start">
                                                <Link><Trash3 style={{ marginTop: '2em', marginLeft: '-1em' }} size={20} color="black" onClick={e => handleRemoveFilter(e, item)} /></Link>
                                            </Col>
                                        </Row>
                                    )
                                }
                            })}
                        </Card.Body>
                    </Card.Body>
                </Card>
                <div className="d-flex justify-content-center mt-5">
                    <Button type="submit" variant="outline-dark" startIcon={<SearchIcon />} style={{ width: '50%' }}>Procurar</Button>
                </div>
            </Form>
        </Container>
    )
}

export default Search