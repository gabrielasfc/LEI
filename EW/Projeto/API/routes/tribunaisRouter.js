var express = require('express');
var router = express.Router();
var Tribunal = require('../controllers/tribunal')
var verify = require('../verify/verify')


router.get('/', verify.userAccess, function (req, res, next) {
    Tribunal.list()
        .then(data => res.status(200).json(data))
        .catch(error => res.status(523).json({ error: "Erro na obtenção da lista de tribunais" }))
})

router.get('/:id', verify.userAccess, function (req, res, next) {
    Tribunal.getTribunal(req.params.id)
        .then(data => res.status(200).json(data))
        .catch(error => res.status(522).json({ error: "Erro na obtenção do tribunal" }))
})

router.delete('/:id', verify.adminAccess, function (req, res, next) {
    Tribunal.deleteAcordao(req.params.id)
        .then(data => res.status(200).json(data))
        .catch(error => res.status(524).json({ error: "Erro na deleção do tribunal" }))
})


router.put('/:id', verify.adminAccess, function (req, res, next) {
    Tribunal.updateTribunal(req.body)
        .then(data => res.status(201).json(data))
        .catch(error => res.status(525).json({ error: "Erro a atualizar tribunal." }))
})


router.post('/', verify.adminAccess, function (req, res, next) {
    console.log(req.body)
    Tribunal.addTribunal(req.body)
        .then(data => res.status(201).json(data))
        .catch(error => res.status(526).json({ error: "Erro a adicionar tribunal." }))
})


module.exports = router;
