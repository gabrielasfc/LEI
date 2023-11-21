using Dapper.Contrib.Extensions;
using src.Data.Data;
using Dapper;

namespace src.Data.BusinessLogic.SubCompras;

[Table("Compra")]
public class Compra
{
    [Key]
    public int idCompra { get; set; }
    public string nomeFaturacao { get; set; }
    public string moradaEntrega { get; set; }
    public string telemovel { get; set; }
    public float valorTotal { get; set; }
    public DateTime timestampCompra { get; set; }
    public int nifCliente { get; set;}

    public Compra(int idCompra, string nomeFaturacao, string moradaEntrega, string telemovel, float valorTotal, DateTime timestamp, int nifCliente)
    {
        this.idCompra = idCompra;
        this.nomeFaturacao = nomeFaturacao;
        this.moradaEntrega = moradaEntrega;
        this.telemovel = telemovel;
        this.valorTotal = valorTotal;
        this.timestampCompra = timestamp;
        this.nifCliente = nifCliente;
    }

    public Compra(string nomeFaturacao, string moradaEntrega, string telemovel, float valorTotal, DateTime timestamp, int nifCliente)
    {
        this.nomeFaturacao = nomeFaturacao;
        this.moradaEntrega = moradaEntrega;
        this.telemovel = telemovel;
        this.valorTotal = valorTotal;
        this.timestampCompra = timestamp;
        this.nifCliente = nifCliente;
    }

    public Compra()
    {

    }

    public override bool Equals(object? obj)
    {
        return obj is Compra compra &&
               this.idCompra == compra.idCompra &&
               this.nomeFaturacao.Equals(compra.nomeFaturacao) &&
               this.moradaEntrega.Equals(compra.moradaEntrega) &&
               this.telemovel.Equals(compra.telemovel) &&
               this.valorTotal == compra.valorTotal &&
               this.timestampCompra.Equals(compra.timestampCompra) &&
               this.nifCliente == compra.nifCliente;
    }

    public override string ToString()
    {
        return this.idCompra + ", " + this.nomeFaturacao + ", " + this.moradaEntrega + ", " + this.telemovel + ", " + this.valorTotal + ", " + this.timestampCompra + ", " + this.nifCliente;
    }

}