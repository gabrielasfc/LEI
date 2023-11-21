using System;
namespace src.Data.BusinessLogic.SubUsers;

public interface ISubUtilizadores
{
    public Task<IEnumerable<Cliente>> GetClientes();

    public Task<IEnumerable<Vendedor>> GetVendedores();

    public Task<Cliente> GetCliente(int nifCliente);

    public Task<Vendedor> GetVendedor(int nifVendedor);

    public Task<int> GetAvaliacao(int nifCliente, int idProduto);

    public void RegistarCliente(String nome, String email, String password, int nifCliente);

    public void RegistarVendedor(String nome, String email, String password, int nifCliente);

    public Task<int> Autenticar(int nif, String password);
}

