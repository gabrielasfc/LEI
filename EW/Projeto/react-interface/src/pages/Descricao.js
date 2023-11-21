import {
  useParams,
  useSearchParams,
  Link,
  Navigate,
  Redirect,
} from "react-router-dom";
import { useState, useEffect, React, useRef } from "react";
import Button from "@mui/material/Button";
import {
  Container,
  ListGroup,
  ListGroupItem,
  Card,
  Modal,
  Form,
  FloatingLabel,
  Row,
} from "react-bootstrap";
import { Button as BootstrapButton } from "react-bootstrap";
import { Eye, Pencil, Trash3, Heart, HeartFill } from "react-bootstrap-icons";
import { ToastContainer, toast } from "react-toastify";
import NavBar from "../components/NavBar";
import NoPage from "../pages/NoPage";
import axios from "axios";
import env from "../config/env";
import jwt_decode from "jwt-decode";

function Descricao() {
  const [record, setRecord] = useState(null);
  const [recordFiltered, setRecordFiltered] = useState(null);
  const [showModal, setShowModal] = useState(false);
  const [Edit, setEdit] = useState(null);
  const [deleteItemID, setDeleteItemID] = useState(null);
  const formRef = useRef(null);

  const fetchData = async () => {
    const response = await axios
      .get(env.apiDescricaoAccessPoint + `?token=${localStorage.token}`)
      .then((response) => {
        setRecord(response.data);
        setRecordFiltered(response.data);
      })
      .catch((error) => {
        setRecord("NoPage");
      });
  };

  useEffect(() => {
    if (Edit === "add" && formRef.current) {
      formRef.current.scrollIntoView({ behavior: "smooth" });
    }
    fetchData();
  }, [Edit]);

  try {
    var decodedToken = jwt_decode(localStorage.getItem("token"));
  } catch {
    return <Navigate to="/login" />;
  }

  const handleShowModal = (event, id) => {
    setDeleteItemID(id);
    setShowModal(true);
  };

  const handleHideModal = () => {
    setShowModal(false);
    setDeleteItemID(null);
  };

  const handleEdit = async (event, id) => {
    setEdit(id);
  };

  const handleDelete = async (event, id) => {
    try {
      await axios.delete(
        env.apiDescricaoAccessPoint + `/${id}?token=${localStorage.token}`
      );

      toast.success("O registo foi removido com sucesso!", {
        position: toast.POSITION.TOP_CENTER,
      });
    } catch (error) {
      toast.error("Não foi possível remover o registo!", {
        position: toast.POSITION.TOP_CENTER,
      });
    }

    handleHideModal();
    fetchData();
    return <Navigate to="/" />;
  };

  function iteratorToDictionary(iterator) {
    const dictionary = {};

    for (const item of iterator) {
      const [key, value] = item;
      dictionary[key] = value;
    }

    return dictionary;
  }

  const handleEditCheck = async (event, id) => {
    event.preventDefault();
    const data = new FormData(event.target);
    try {
      await axios.put(
        env.apiDescricaoAccessPoint + `/${id}?token=${localStorage.token}`,
        iteratorToDictionary(data.entries())
      );

      toast.success("O registo foi alterado com sucesso", {
        position: toast.POSITION.TOP_CENTER,
      });

      setEdit(null);
    } catch (error) {
      toast.error("Não foi possível alterar o registo!", {
        position: toast.POSITION.TOP_CENTER,
      });
    }
    fetchData();
    return <Navigate to="/descricoes" />;
  };

  const handleCancel = (event) => {
    setEdit(null);
  };
  const handleAddButton = (event) => {
    setEdit("add");
  };

  function Lista(obj) {
    return (
      <div className="d-flex flex-row">
        <Container>
          <b>{obj["Nome"]}</b>
        </Container>
        {decodedToken.level >= 100 && (
          <Container className="d-flex justify-content-end px-3">
            <Link>
              {" "}
              <Pencil
                size={20}
                color="black"
                className="mx-3"
                onClick={(event) => handleEdit(event, obj["_id"])}
              />{" "}
            </Link>
            <>
              <Link>
                <Trash3
                  size={20}
                  color="black"
                  className="mx-3"
                  onClick={(event) => handleShowModal(event, obj._id)}
                />
              </Link>
              <Modal show={showModal} onHide={handleHideModal}>
                <Modal.Header closeButton>
                  <Modal.Title>Confirmação de Remoção</Modal.Title>
                </Modal.Header>
                <Modal.Body>
                  <div className="alert alert-danger">
                    Tem a certeza que pretende remover este acórdão?
                  </div>
                </Modal.Body>
                <Modal.Footer>
                  <Button variant="default" onClick={handleHideModal}>
                    Cancelar
                  </Button>
                  <Button
                    variant="danger"
                    onClick={(event) => handleDelete(event, obj._id)}
                  >
                    Remover
                  </Button>
                </Modal.Footer>
              </Modal>
            </>
          </Container>
        )}
      </div>
    );
  }

  const handleSearchChange = async (event) => {
    event.preventDefault();
    const regex = new RegExp(event.target.value, "i");
    setRecordFiltered(
      record.filter(function (elem) {
        return elem["Nome"].search(regex) !== -1;
      })
    );
  };

  return (
    <>
      <ToastContainer />
      <NavBar />
      <Container>
        <hr className="mt-4 mb-4" />
        <div className="d-flex justify-content-start mb-4"></div>
        <Card
          className="d-flex justify-content-center"
          style={{ boxShadow: "0 0.15rem 1.75rem 0 rgb(33 40 50 / 15%)" }}
        >
          <Card.Body>
            <div className="d-flex justify-content-end mb-4"></div>
            {/* OUTRAS INFORMAÇÕES */}
            <Container className="my-4 b-4">
              <h4> Campos</h4>
              <ListGroup>
                <Form>
                  <Form.Control
                    className="d-flex mb-3"
                    type="search"
                    placeholder="Pesquisa livre..."
                    aria-label="Procurar"
                    onChange={handleSearchChange}
                  />
                </Form>
                {Array.isArray(record) && record !== "NoPage" ? (
                  <div>
                    {recordFiltered.length >= 1 ? (
                      recordFiltered.map((obj) => (
                        <ListGroup className="list-group-flush" key={obj}>
                          <ListGroupItem>
                            {Edit === obj["_id"] ? (
                              <div>
                                <Form
                                  onSubmit={(event) =>
                                    handleEditCheck(event, obj._id)
                                  }
                                >
                                  <FloatingLabel
                                    controlId="floatingInput"
                                    className="mb-3 form-outline"
                                    label="Nome"
                                  >
                                    <Form.Control
                                      type="text"
                                      placeholder="Nome"
                                      defaultValue={obj["Nome"]}
                                      name="Nome"
                                    />
                                  </FloatingLabel>
                                  <FloatingLabel
                                    className="mb-3 form-outline"
                                    label="Descrição"
                                  >
                                    <textarea
                                      className="form-control"
                                      id="outlined-uncontrolled"
                                      name="Desc"
                                      style={{ height: "200px" }}
                                      defaultValue={obj["Desc"]}
                                    />
                                  </FloatingLabel>
                                  <Row>
                                    <div className="mb-5 d-flex justify-content-center padding-bottom">
                                      <Button
                                        type="submit"
                                        variant="outline-dark"
                                      >
                                        Registar Alterações
                                      </Button>
                                      <Button
                                        type="button"
                                        onClick={handleCancel}
                                        variant="outline-dark"
                                      >
                                        Cancelar
                                      </Button>
                                    </div>
                                  </Row>
                                </Form>
                              </div>
                            ) : (
                              Lista(obj)
                            )}
                          </ListGroupItem>
                          <ListGroupItem>{obj["Desc"]}</ListGroupItem>
                        </ListGroup>
                      ))
                    ) : (
                      <Card
                        className="d-flex justify-content-center"
                        style={{
                          boxShadow: "0 0.15rem 1.75rem 0 rgb(33 40 50 / 15%)",
                          height: "3rem",
                        }}
                      >
                        <Card.Body>
                          <div className="d-flex justify-content-center mb-3 mt-3">
                            {" "}
                            Não está disponibilizada nenhuma descrição de um
                            Campo.
                          </div>
                        </Card.Body>
                      </Card>
                    )}
                  </div>
                ) : (
                  <ListGroupItem>{record}</ListGroupItem>
                )}
              </ListGroup>
            </Container>
          </Card.Body>
        </Card>
      </Container>
    </>
  );
}

export default Descricao;
