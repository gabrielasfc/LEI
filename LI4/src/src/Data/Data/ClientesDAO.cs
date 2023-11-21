using System;
using Dapper;
using Dapper.Contrib;
using Dapper.Contrib.Extensions;
using Microsoft.Data.SqlClient;
using src.Data.BusinessLogic;

namespace src.Data.Data;

public class ClientesDAO
{
    private static ClientesDAO clientes = null;

    private ClientesDAO()
    {
    }

    public static ClientesDAO GetInstance()
    {
        if (clientes == null)
        {
            clientes = new ClientesDAO();
        }

        return clientes;
    }

	public Cliente Get(int id)
	{
		const string connectionString = DAOConfig.URL;
		Cliente cliente;
		using (var connection = new SqlConnection(connectionString))
		{
			cliente = connection.Get<Cliente>(id);
		}
		return cliente;
	}

	public Cliente Insert(Cliente cliente)
    {
        const string connectionString = DAOConfig.URL;

        using (var connection = new SqlConnection(connectionString))
        {
            connection.Insert<Cliente>(cliente);
        }

        return cliente;
    }


    public void Delete(int id)
    {
        
    }

    public IEnumerable<Cliente> GetAll()
    {
        const string connectionString = DAOConfig.URL;

        IEnumerable<Cliente> clientes;
        using (var connection = new SqlConnection(connectionString))
        {
            clientes = connection.GetAll<Cliente>();
        }
        return clientes;
    }

    public int GetAvaliacao(int nifCliente, int idProduto)
    {
        const string connectionString = DAOConfig.URL;
        IEnumerable<int> ret;

        using (var connection = new SqlConnection(connectionString))
        {
		var parameters = new { NIFCliente = nifCliente, IDProduto = idProduto };
        	ret = connection.Query<int>("SELECT valorAval FROM Avaliacao WHERE (nifCliente=@NIFCliente and idProduto=@IDProduto)", parameters);
        }

        return ret.FirstOrDefault();
    }
}


