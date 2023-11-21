var express = require("express")
var router = express.Router()
var Acordao = require("../controllers/acordao")
var verify = require("../verify/verify")

/* GET home page. */
router.get("/", verify.userAccess, function (req, res, next) {
    var skip = 0, limit = 75 // Por default só manda 75 acordaos => impedir sobrecarga

    if (req.query.skip) {
        skip = req.query.skip
        delete req.query.skip
    }

    if (req.query.limit) {
        limit = req.query.limit
        delete req.query.limit
    }

    if (req.query.lastID) {
        req.query["_id"] = { $lt: parseInt(req.query.lastID) };
        delete req.query.lastID;
    }

    if (req.query.search) {
        req.query["$text"] = { $search: `\"${req.query.search}\"` }
        delete req.query.search
    }

    Object.keys(req.query).forEach(key => {
        if (typeof req.query[key] === 'string' && key !== "_id") {
            req.query[key] = { $regex: req.query[key], $options: "i" }
        }
    })

    Acordao.list(req.query, skip, limit)
        .then((data) => {
            res.status(200).json(data)
        })
        .catch((error) =>
            res.status(521).json({
                error: error,
                message: "Erro na obtenção da lista de acordãos",
            })
        )
})

router.get("/number", verify.userAccess, function (req, res, next) {
    if (req.query.search) {
        req.query["$text"] = { $search: `\"${req.query.search}\"` }
        delete req.query.search
    }

    Acordao.getAcordaosNumber(req.query)
        .then((data) => res.status(200).json(data))
        .catch((error) => res.status(523).json({ error: "Erro na obtenção do número de acordãos" }))
})

router.get("/:id", verify.userAccess, function (req, res, next) {
    try {
        Acordao.getAcordao(req.params.id)
            .then((data) => res.status(200).json(data))
            .catch((error) => res.status(522).json({ error: "Erro na obtenção do acordão" }))
    }
    catch (e) {
        res.jsonp({ error: e.message })
    }
})

router.post("/", verify.producerAccess, function (req, res, next) {
    Acordao.addAcordao(req.body)
        .then((data) => res.status(200).json(data))
        .catch((error) => res.status(523).json({ error: "Erro na criação do acordão" }))
})

router.delete("/:id", verify.adminAccess, function (req, res, next) {
    Acordao.deleteAcordao(req.params.id)
        .then((data) => res.status(200).json(data))
        .catch((error) => res.status(524).json({ error: "Erro na deleção do acordão" }))
})

router.put("/:id", verify.adminAccess, function (req, res) {
    Acordao.updateAcordao(req.body)
        .then((data) => res.status(201).json(data))
        .catch((error) => res.status(525).json({ error: "Erro a atualizar acordão." }))
})

module.exports = router
