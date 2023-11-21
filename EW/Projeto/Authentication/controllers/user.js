// Controlador para o modelo User

var User = require('../models/user')

// Devolve a lista de Users
module.exports.list = () => {
    return User
            .find()
            .sort('name')
            .then(response => {
                return response
            })
            .catch(error => {
                return error
            })
}


module.exports.getUser = username => {
    return User
            .findOne({username: username})
            .then(response => {
                return response
            })
            .catch(error => {
                return error
            })
}


module.exports.checkEmail = (email) => {
    return User
            .findOne({email: email})
            .then(response => {
                return response
            })
            .catch(error => {
                return error
            })
}


module.exports.checkUsername = (username) => {
    return User
            .findOne({username: username})
            .then(response => {
                return response
            })
            .catch(error => {
                return error
            })
}


module.exports.getFavorites = username => {
    return User
            .findOne({username: username}, {favorites: 1})
            .then(response => {
                return response
            })
            .catch(error => {
                console.log(error)
                return error
            })
}


module.exports.addUser = u => {
    return User.create(u)
            .then(response => {
                return response
            })
            .catch(error => {
                return error
            })
}


module.exports.updateUser = (username, info) => {
    return User.updateOne({username: username}, info)
            .then(response => {
                return response
            })
            .catch(error => {
                return error
            })
}


module.exports.updateFavorite = (username, favorite) => {
    return User
        	.updateOne({username: username}, {$addToSet : {favorites: favorite}})
            .then(response => {
                return response
            })
            .catch(error => {
                return error
            })
}


module.exports.removeFavorite = (username, id) => {
    return User.updateOne({ username: username }, { $pull: { favorites: { _id: id } } })
      .then(response => {
        return response;
      })
      .catch(error => {
        return error;
      });
  };


module.exports.updateAccess = (username, date) => {
    return User.updateOne({username: username}, {lastAccess: date})
            .then(response => {
                return response
            })
            .catch(error => {
                return error
            })
}

module.exports.updateUserPassword = (username, pwd) => {
    return User.updateOne({username: username}, pwd)
            .then(response => {
                return response
            })
            .catch(error => {
                return error
            })
}


module.exports.deleteUser = username => {
    return User.deleteOne({username: username})
            .then(response => {
                return response
            })
            .catch(error => {
                return error
            })
}
 
