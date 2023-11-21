var express = require('express');
var router = express.Router();
var Field = require('../controllers/field')
var verify = require('../verify/verify')


router.get('/', verify.userAccess, function (req, res, next) {
    Field.list()
        .then(data => res.status(200).json(data))
        .catch(error => res.status(523).json({ error: "Erro na obtenção da lista de campos" }))
})


router.delete('/:id', verify.adminAccess, function (req, res, next) {
    Field.deleteField(req.params.id)
        .then(data => res.status(200).json(data))
        .catch(error => res.status(524).json({ error: "Erro na deleção do campo" }))
})


router.put('/:id', verify.adminAccess, function (req, res, next) {
    Field.updateField(req.body)
        .then(data => res.status(201).json(data))
        .catch(error => res.status(525).json({ error: "Erro a atualizar campo" }))
})


router.post('/', verify.adminAccess, function (req, res, next) {
    Field.addField(req.body)
        .then(data => {res.status(201).json(data)})
        .catch(error => res.status(526).json({ error: "Erro a adicionar campo" }))
})


module.exports = router;
