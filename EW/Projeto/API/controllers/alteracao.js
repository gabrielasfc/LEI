var Alteracao = require("../models/alteracao");

module.exports.list = (query, skip, limit) => {
    return Alteracao.find(query)
        .skip(skip)
        .limit(limit)
        .sort({_id: -1})
        .then((response) => {
            return response;
        })
        .catch((error) => {
            return error;
        });
};

module.exports.getAlteracao = (id) => {
    if (isNaN(parseInt(id)))
        throw new Error('O tipo do identificador do registo apresentado não corresponde a um número!')
    return Alteracao.findOne({ _id: id })
        .then((response) => {
            return response;
        })
        .catch((error) => {
            return error;
        });
};

module.exports.getAlteracaosNumber = (query) => {
    return Alteracao.find(query)
        .count()
        .then((response) => {
            return response;
        })
        .catch((error) => {
            return error;
        });
};

module.exports.addAlteracao = (alteracao) => {
    alteracao["_id"] = new mongoose.Types.ObjectId()
    return Alteracao.create(alteracao)
                .then((response2) => {
                    return response2;
                })
                .catch((error) => {
                    return error;
                });
        };

module.exports.deleteAlteracao = (id) => {
    return Alteracao.deleteOne({ _id: id })
        .then((response) => {
            return response;
        })
        .catch((error) => {
            return error;
        });
};

module.exports.updateAlteracao = (alteracao) => {
    return Alteracao.updateOne({ _id: alteracao._id }, alteracao)
        .then((response) => {
            return response;
        })
        .catch((error) => {
            return error;
        });
};
