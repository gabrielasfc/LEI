using System;
using Dapper;
using Dapper.Contrib;
using Dapper.Contrib.Extensions;
using Microsoft.Data.SqlClient;
using src.Data.BusinessLogic.SubFeiras;

namespace src.Data.Data;

public class ProdutosDAO
{
    private static ProdutosDAO singleton = null;
    private ProdutosDAO()
    {
    }

    public static ProdutosDAO GetInstance()
    {
        if (singleton == null)
        {
            singleton = new ProdutosDAO();
        }

        return singleton;
    }
    public Produto Get(int id)
    {
        const string connectionString = DAOConfig.URL;
        Produto p;

        using (var connection = new SqlConnection(connectionString))
        {
            p = connection.Get<Produto>(id);
        }

        return p;
    }

    public IEnumerable<Produto> GetProdutosFeira(string nomeFeira)
    {
        const string connectionString = DAOConfig.URL;
        IEnumerable<Produto> ps = new List<Produto>();

        using (var connection = new SqlConnection(connectionString))
        {
            var parameters = new { NomeFeira = nomeFeira };
            IEnumerable<int> ids = connection.Query<int>("SELECT idProduto FROM Produto WHERE nomeFeira=@NomeFeira", parameters);

            foreach(int id in ids)
            {
                ps = ps.Append(Get(id));
            }
        }
        return ps;
    }

    public IEnumerable<Produto> GetProdutosVendedor(int nif)
    {
        const string connectionString = DAOConfig.URL;
        IEnumerable<Produto> ps = new List<Produto>();

        using (var connection = new SqlConnection(connectionString))
        {   
            var parameters = new { NifVendedor = nif };
            IEnumerable<int> ids = connection.Query<int>("SELECT idProduto FROM Produto WHERE nifVendedor= @NifVendedor", parameters);

            foreach (int id in ids)
            {
                ps = ps.Append(Get(id));
            }
        }
        return ps;
    }

    public IEnumerable<Produto> GetFavs(int id)
    {
        const string connectionString = DAOConfig.URL;
        IEnumerable<int> idsP;

        using (var connection = new SqlConnection(connectionString))
        {
            var parameters = new {NifCliente = id};
            idsP = connection.Query<int>("SELECT idProduto FROM Favorito where nifCliente=@NifCliente", parameters);
        }

        IEnumerable<Produto> favs = new List<Produto>();
        foreach (int idP in idsP)
        {
            favs = favs.Append(Get(idP));
        }

        return favs;
    }

    public IEnumerable<Tuple<int, int>> GetAvaliacoes(int nifCliente)
    {
        const string connectionString = DAOConfig.URL;
        IEnumerable<Tuple<int, int>> idsP;

        using (var connection = new SqlConnection(connectionString))
        {
            var parameters = new { NifClient = nifCliente};
            idsP = connection.Query<Tuple<int, int>>("SELECT idProduto,valorAval FROM Avaliacao WHERE nifCliente=@NifCliente", parameters);
        }

        return idsP;
    }


    public Produto Insert(Produto p)
    {
        const string connectionString = DAOConfig.URL;
        long id;

        using (var connection = new SqlConnection(connectionString))
        {
            id = connection.Insert<Produto>(p);
        }

        return Get((int) id);
    } 

    public void InsertAvaliacao(int nifCliente, int idProduto, int valorAval)
    {
        const string connectionString = DAOConfig.URL;

        using (var connection = new SqlConnection(connectionString))
        {
            var parameters1 = new { ValorAval = valorAval, NifCliente = nifCliente, IdProduto = idProduto};
            int affected = connection.Execute("UPDATE Avaliacao SET valorAval=@ValorAval WHERE (nifCliente=@NifCliente and idProduto=@IdProduto)", parameters1);
            if (affected == 0)
            {
                var parameters2 = new { NifCliente = nifCliente, IdProduto = idProduto, ValorAval = valorAval};
                connection.Execute("INSERT INTO Avaliacao (nifCliente, idProduto, valorAval) VALUES (@NifCliente, @IdProduto, @ValorAval)", parameters2);
            }
        }
    }

    public void UpdateAvaliacaoProduto(int idProduto)
    {
        const string connectionString = DAOConfig.URL;

        using (var connection = new SqlConnection(connectionString))
        {
            IEnumerable<int> avaliacoes = connection.Query<int>("SELECT valorAval FROM Avaliacao WHERE idProduto=" + idProduto);

            float soma = 0;
            int n = 0;
            foreach(var avaliacao in avaliacoes)
            {
                soma += avaliacao;
                n++;
            }

            float avaliacaoMedia = soma / (float)n;

            var parameters = new { AvaliacaoMedia = avaliacaoMedia, IdProduto = idProduto };
            connection.Execute("UPDATE Produto SET avaliacaoMedia= @AvaliacaoMedia WHERE idProduto= @IdProduto", parameters);
        }
    }

    public Produto Delete(int key)
    {
        Produto p = Get(key);

        const string connectionString = DAOConfig.URL;

        using (var connection = new SqlConnection(connectionString))
        {
            connection.Delete<Produto>(p);
        }

        return p;
    }

   public IEnumerable<Produto> GetAll() 
   {
        const string connectionString = DAOConfig.URL;
        IEnumerable<Produto> produtos;

        using (var connection = new SqlConnection(connectionString))
        {
            produtos = connection.GetAll<Produto>();
        }

        return produtos;
    }


    public int GetAvaliacaoMediaProduto(int idProduto)
    {
        const string connectionString = DAOConfig.URL;
        IEnumerable<int> avals;

        using (var connection = new SqlConnection(connectionString))
        {
            var parameters = new { IdProduto = idProduto};
            avals = connection.Query<int>("SELECT valorAval FROM Avaliacao WHERE idProduto=@IdProduto", parameters);
        }

        int soma = avals.Sum();
        return soma / (avals.Count());
    }

    public IEnumerable<(DateTime timestamp, float valorVenda, int quantidade, int nifCliente)>GetComprasProduto(int idProduto)
    {
        const string connectionString = DAOConfig.URL;

        IEnumerable<(DateTime, float, int, int)> compras = new List<(DateTime, float, int, int)>();

        using (var connection = new SqlConnection(connectionString))
        {
            var parameters1 = new { IdProduto = idProduto};
            IEnumerable<(int, float, int)> transacoes = connection.Query<(int, float, int)>("SELECT idCompra,valorVenda,quantidade FROM ProdutoDaCompra WHERE idProduto=@IdProduto", parameters1);

            foreach(var transacao in transacoes)
            {
                var parameters2 = new { IdCompra = transacao.Item1 };
                IEnumerable<(int, DateTime)> compra = connection.Query<(int, DateTime)>("SELECT nifCliente, timestampCompra FROM Compra WHERE idCompra=@IdCompra", parameters2);
                compras = compras.Append((compra.First().Item2, transacao.Item2, transacao.Item3, compra.First().Item1));
            }
        }


        return compras;
    }
}
