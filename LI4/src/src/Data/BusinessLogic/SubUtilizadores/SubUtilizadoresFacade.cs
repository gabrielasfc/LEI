using System;
using src.Data.Data;
using src.Data.BusinessLogic.SubFeiras;
using src.Data.BusinessLogic.Excecoes;

namespace src.Data.BusinessLogic.SubUsers;

public class SubUtilizadoresFacade : ISubUtilizadores
{
    private ClientesDAO Clientes;
    private VendedoresDAO Vendedores;

    public SubUtilizadoresFacade()
    {
        Clientes = ClientesDAO.GetInstance();
        Vendedores = VendedoresDAO.GetInstance();
    }


    public void RegistarCliente(String nome, String email, String password, int nifCliente)
    {
        if( Clientes.Get(nifCliente) == null )
        {
            Cliente cliente = new Cliente(nifCliente, nome, email, password);
            Clientes.Insert(cliente);
        }
        else
        {
            throw new AlreadyRegisteredException("Conta já registada");
        }
    }

    public void RegistarVendedor(String nome, String email, String password, int nifVendedor)
    {
        if (Vendedores.Get(nifVendedor) == null)
        {
            Vendedor vendedor = new Vendedor(nifVendedor, nome, email, password);
            Vendedores.Insert(vendedor);
        }
        else
        {
            throw new AlreadyRegisteredException("Conta já registada");
        }
    }

    public Task<int> Autenticar(int nif, String password)
    {
        Cliente cliente = Clientes.Get(nif);
            
        if(cliente != null)
        {
            if (cliente.passwordCliente.Equals(password))
            {
                return Task.FromResult(1);
            }
            else
            {
                throw new WrongPasswordException("Password inválida!");
            }
        }

        Vendedor vendedor = Vendedores.Get(nif);

	    if (vendedor != null)
		{
			if (vendedor.passwordVendedor.Equals(password))
			{
				return Task.FromResult(2);
			}
			else
			{
				throw new WrongPasswordException("Password inválida!");
			}
		}   
		throw new NonExistentAccountException("Conta inexistente!");
	}

    public Task<IEnumerable<Cliente>> GetClientes()
    {
        return Task.FromResult(Clientes.GetAll());
    }

    public Task<IEnumerable<Vendedor>> GetVendedores()
    {
        return Task.FromResult(Vendedores.GetAll());
    }

    public Task<Cliente> GetCliente(int nifCliente)
    {
        return Task.FromResult(Clientes.Get(nifCliente));
    }

    public Task<Vendedor> GetVendedor(int nifVendedor)
    {
        return Task.FromResult(Vendedores.Get(nifVendedor));
    }

    public Task<int> GetAvaliacao(int nifCliente, int idProduto)
    {
        return Task.FromResult(Clientes.GetAvaliacao(nifCliente,idProduto));
    }
}


