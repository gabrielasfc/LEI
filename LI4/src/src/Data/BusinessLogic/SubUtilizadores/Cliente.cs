using Dapper.Contrib.Extensions;
using src.Data.Data;
using System;
namespace src.Data.BusinessLogic;

[Table("Cliente")]
public class Cliente
{
    [ExplicitKey]
    public int nifCliente { get; set; }
    public String nome { get; set; }
    public String email { get; set; }
    public String passwordCliente { get; set; }

    public Cliente() { }

    public Cliente(int clientNif, string name, string email, string password)
    {
        this.nifCliente = clientNif;
        this.nome = name;
        this.email = email;
        this.passwordCliente = password;
    }

    public override bool Equals(object? obj)
    {
        return obj is Cliente client &&
               nifCliente == client.nifCliente &&
               nome.Equals(client.nome) &&
               email.Equals(client.email) &&
               passwordCliente.Equals(client.passwordCliente);
    }

    public override string ToString()
    {
        return this.nifCliente + ", " + this.nome + ", " + this.email + ", " + this.passwordCliente;
    }

}

