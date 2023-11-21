import { Navbar, Nav, Container, NavDropdown } from 'react-bootstrap';
import { Navigate } from 'react-router-dom';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faHeart, faUser } from '@fortawesome/free-solid-svg-icons';
import jwt_decode from 'jwt-decode'
import Cookies from 'js-cookie'

function NavBar() {
    try {
        var decodedToken = jwt_decode(localStorage.getItem('token'))
    }
    catch {
        return (<Navigate to="/login" />)
    }

    const handleLogout = () => {
        localStorage.removeItem('token')
        Cookies.remove('token')
    }

    return (
        <>
            <Navbar bg="dark" variant="dark" expand="lg" style={{ '--bs-navbar-padding-y': '1rem' }}>
                <Container style={{ 'maxWidth': '95%' }}>
                    <Navbar.Brand href="/">Acórdãos</Navbar.Brand>
                    <Navbar.Collapse>
                        <Nav >
                            <Nav.Link href="/">Início</Nav.Link>
                            <Nav.Link href="/descricoes">Acerca</Nav.Link>
                            {decodedToken.level === 100 && <Nav.Link href="/dashboard">Dashboard</Nav.Link>}
                            {(decodedToken.level >= 20) && <Nav.Link href="/insert">Inserir Acórdão</Nav.Link>}
                        </Nav>

                        <Nav className='ms-auto'>
                            <Nav.Link href="/favorites" className='me-3 pe-3'>
                                <FontAwesomeIcon icon={faHeart} size='lg' />
                            </Nav.Link>

                            <NavDropdown className='pe-5 me-5' title={<FontAwesomeIcon icon={faUser} size='lg' />} id="account-dropdown">
                                <NavDropdown.Item href="/profile">Perfil</NavDropdown.Item>
                                <NavDropdown.Divider />
                                <NavDropdown.Item href="/" onClick={handleLogout}>Sair</NavDropdown.Item>
                            </NavDropdown>
                        </Nav>
                    </Navbar.Collapse>
                </Container>
            </Navbar>
        </>
    );
}

export default NavBar;