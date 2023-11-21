using Dapper.Contrib.Extensions;
using System;
namespace src.Data.BusinessLogic.SubFeiras;

[Table("Produto")]
public class Produto
{
    [Key]
    public int idProduto { get; set; }
    public string nome { get; set; }
    public float preço { get; set; }
    public int stock { get; set; }
    public string descricao { get; set; }
    public string categoria { get; set; }
    public float avaliacaoMedia { get; set; }
    public float fatorAceitacao { get; set; }
    public float fatorTolerancia { get; set; }
    public float fatorResposta { get; set; }

    public string nomeFeira { get; set; }

    public int nifVendedor { get; set; } 


    public Produto(string nomeProduto, float preco, int stockP, string descricaoP, string categoriaP, float avaliacao, float fatorAceitacaoP, float fatorToleranciaP, float fatorRespostaP, string nomeF, int nifV)
    {
        nome = nomeProduto;
        preço = preco;
        stock = stockP;
        descricao = descricaoP;
        categoria = categoriaP;
        avaliacaoMedia = avaliacao;
        fatorAceitacao = fatorAceitacaoP;
        fatorTolerancia = fatorToleranciaP;
        fatorResposta = fatorRespostaP;
        nomeFeira = nomeF;
        nifVendedor = nifV;
    }

    public Produto() { }

    public override bool Equals(object? obj)
    {
        return obj is Produto produto &&
               idProduto == produto.idProduto &&
               nome.Equals(produto.nome) &&
               preço == produto.preço &&
               stock == produto.stock &&
               descricao.Equals(produto.descricao) &&
               categoria.Equals(produto.categoria) &&
               avaliacaoMedia == produto.avaliacaoMedia &&
               fatorAceitacao == produto.fatorAceitacao &&
               fatorTolerancia == produto.fatorTolerancia &&
               fatorResposta == produto.fatorResposta &&
               nomeFeira.Equals(produto.nomeFeira) &&
               nifVendedor == produto.nifVendedor;
    }

    public override string ToString()
    {
        return this.idProduto + ", " + this.nome + ", " + this.preço + ", " + 
               this.stock + ", " + this.descricao + ", " + this.categoria + ", " +
               this.avaliacaoMedia + ", " + this.fatorAceitacao + ", " + this.fatorTolerancia + ", " + 
               this.fatorResposta + ", " + this.nomeFeira + ", " + this.nifVendedor;
    }

}

