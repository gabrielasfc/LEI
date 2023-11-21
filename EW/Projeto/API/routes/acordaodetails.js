var express = require("express");
var router = express.Router();
var Acordao = require("../controllers/acordao_details");
var verify = require("../verify/verify")

/* GET home page. */
router.get("/", verify.userAccess, function (req, res, next) {
    Acordao.list()
        .then((data) => {
            res.status(200).jsonp(data);
        })
        .catch((error) =>
            res.status(521).json({
                error: error,
                message: "Erro na obtenção da lista de acordãos",
            })
        );
});

router.post("/", verify.userAccess, function (req, res, next) {
    Acordao.addAcordao(req.body)
        .then((data) => {
            console.log(data);
            res.status(200).json(data);
        })
        .catch((error) =>
            res
                .status(523)
                .json({ error: error, message: "Erro na criação do acordão" })
        );
});

router.put("/:id", verify.userAccess, function (req, res, next) {
    Acordao.alteraAcordao(req.params.id, req.body)
        .then((data) => res.status(200).json(data))
        .catch((error) =>
            res
                .status(523)
                .json({ error: error, message: "Erro na criação do acordão" })
        );
});

router.delete("/:id", verify.userAccess, function (req, res, next) {
    Acordao.deleteAcordao(req.params.id)
        .then((data) => res.status(200).json(data))
        .catch((error) =>
            res
                .status(523)
                .json({ error: error, message: "Erro na criação do acordão" })
        );
});

module.exports = router;
