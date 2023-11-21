var jwt = require('jsonwebtoken')

module.exports.userAccess = function (req, res, next) {
    var token = req.query.token || req.body.token
    if(token){
        jwt.verify(token, "Acordaos2023", function(error, payload){
            delete req.query.token;
            if(error) res.status(401).jsonp({error: error})
            else{
                var decodedToken = jwt.decode(token)
                if(decodedToken.level){
                    if(decodedToken.level >= 10) next()
                    else res.status(401).jsonp({error: "Permissão insuficiente!"})
                }
                else res.status(401).jsonp({error: "Permissões inexistentes no token!"})
            }
        })
    }
    else res.status(401).jsonp({error: "Token inexistente!"})
}


module.exports.producerAccess = function (req, res, next) {
    var token = req.query.token || req.body.token
    if(token){
        jwt.verify(token, "Acordaos2023", function(error, payload){
            delete req.query.token;
            if(error) res.status(401).jsonp({error: error})
            else{
                var decodedToken = jwt.decode(token)
                if(decodedToken.level){
                    if(decodedToken.level >= 20) next()
                    else res.status(401).jsonp({error: "Permissão insuficiente!"})
                }
                else res.status(401).jsonp({error: "Permissões inexistentes no token!"})
            }
        })
    }
    else res.status(401).jsonp({error: "Token inexistente!"})
}


module.exports.adminAccess = function (req, res, next) {
    var token = req.query.token || req.body.token
    if(token){
        jwt.verify(token, "Acordaos2023", function(error, payload){
            delete req.query.token;
            if(error) res.status(401).jsonp({error: error})
            else{
                var decodedToken = jwt.decode(token)
                if(decodedToken.level){
                    if(decodedToken.level >= 100) next()
                    else res.status(401).jsonp({error: "Permissão insuficiente!"})
                }
                else res.status(401).jsonp({error: "Permissões inexistentes no token!"})
            }
        })
    }
    else res.status(401).jsonp({error: "Token inexistente!"})
}