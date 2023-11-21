using System;
using Dapper.Contrib.Extensions;
using src.Data.BusinessLogic.SubFeiras;
using src.Data.Data;
namespace src.Data.BusinessLogic;

[Table("Vendedor")]
public class Vendedor
{
    [ExplicitKey]
    public int nifVendedor { get; set; }
    public String nome { get; set; }
    public String email { get; set; }
    public String passwordVendedor { get; set; }

    public Vendedor(int sellerNif, string name, string email, string password)
    {
        this.nifVendedor = sellerNif;
        this.nome = name;
        this.email = email;
        this.passwordVendedor = password;
    }

    public Vendedor() { }

    public override bool Equals(object? obj)
    {
        return obj is Vendedor seller &&
               nifVendedor == seller.nifVendedor &&
               nome.Equals(seller.nome) &&
               email.Equals(seller.email) &&
               passwordVendedor.Equals(seller.passwordVendedor);
    }

    public override string ToString()
    {
        return nifVendedor + ", " + nome + ", " + email + ", " + passwordVendedor;
    }

}

