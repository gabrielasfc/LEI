const mongoose = require("mongoose");

var JurisprudenciasSchema = new mongoose.Schema({
  "Jurisprudência Nacional": [String],
  "Jurisprudência Internacional": [String],
  "Jurisprudência Estrangeira": [String],
  "Jurisprudência Constitucional": [String],
  "Outra Jurisprudência": [String],
});

var LegislacoesSchema = new mongoose.Schema({
  "Legislação Nacional": [String],
  "Legislação Comunitária": [String],
  "Legislação Estrangeira": [String],
});

var acordaoSchema = new mongoose.Schema({
  _id: Number,
  Processo: String,
  Relator: String,
  Descritores: [String],
  "Data do Acordão": String,
  Votação: String,
  Sumário: String,
  "Decisão Texto Integral": String,
  tribunal: String,
  Decisão: String,
  "Meio Processual": String,
  Legislações: LegislacoesSchema,
  "Área Temática 1": [String],
  "Referências Internacionais": [String],
  Jurisprudências: JurisprudenciasSchema,
  "Tribunal Recorrido": String,
  "Processo no Tribunal Recorrido": String,
  "Referência Processo": String,
  "Indicações Eventuais": [String],
  "Nº Convencional": String,
  "Nº do Documento": String,
  Requerente: String,
  Requerido: [String],
  "Data de Entrada": String,
  Objecto: String,
  "Área Temática 2": [String],
  Doutrina: [String],
  "Recusa Aplicação": String,
  "Referência a Pareceres": [String],
  Privacidade: String,
  Apêndice: String,
  "Data do Apêndice": String,
  "Referências Publicação": [String],
  Reclamações: [String],
  Apenso: String,
  "Data da Decisão": String,
  Recurso: String,
  "Juízo ou Secção": String,
  Tribunal: String,
  "Parecer Ministério Publico": String,
  Magistrado: String,
  Acordão: String,
  "Volume dos Acordãos do T.C.": String,
  Autor: String,
  Réu: [String],
  "Data do Acordão 2": String,
});

acordaoSchema.index({ Processo: 1 });
acordaoSchema.index({ "Data do Acordão": 1 });
acordaoSchema.index({ Descritores: 1 });
acordaoSchema.index({ Relator: 1 });
acordaoSchema.index({ tribunal: 1 });
acordaoSchema.index({ "$**": "text" });

module.exports = mongoose.model("acordao", acordaoSchema);
