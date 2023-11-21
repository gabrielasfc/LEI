import NavBar from "../components/NavBar";
import { Container, Row } from "react-bootstrap";
import image_error from '../no_page.png'

const NoPage = () => {
    return (
        <div>
            <NavBar />
            <Container className="d-flex justify-content-center align-items-center">
                <Row className="col-md-8">
                    <img src={image_error} alt="Imagem de erro " />
                </Row>
            </Container>
            <Container className="d-flex justify-content-center align-items-center">
                <h1>Deste um tiro ao lado!</h1>
            </Container>
            <Container className="d-flex justify-content-center align-items-center">
                <h2>A página que procuraste não está disponível!</h2>
            </Container>
        </div>
    );
};

export default NoPage;
