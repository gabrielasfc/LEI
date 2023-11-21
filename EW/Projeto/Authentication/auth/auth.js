var jwt = require('jsonwebtoken')

module.exports.verifyToken = function(req, res, next){
    var myToken = req.query.token || req.body.token
    if(myToken){
        jwt.verify(myToken, "Acordaos2023", function(e, payload){
          if(e){
            res.status(401).jsonp({error: e})
          }
          else{
            next()
          }
        })
      }
      else{
        res.status(401).jsonp({error: "Token inexistente!"})
      }
}