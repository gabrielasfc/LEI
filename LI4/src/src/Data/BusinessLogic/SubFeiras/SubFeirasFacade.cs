using System;
using System.Collections.Generic;
using System.Globalization;
using src.Data.BusinessLogic.Excecoes;
using src.Data.Data;

namespace src.Data.BusinessLogic.SubFeiras;

public class SubFeirasFacade : ISubFeiras
{
    private FeirasDAO Feiras;
    private ProdutosDAO Produtos;

    public SubFeirasFacade()
    {
        this.Feiras = FeirasDAO.GetInstance();
        this.Produtos = ProdutosDAO.GetInstance();
    }

    public Task<IEnumerable<Feira>> GetFeiras()
    {
        return Task.FromResult(Feiras.GetAll());
    }

    public Task<Feira> GetFeira(string nome)
    {
        return Task.FromResult(Feiras.Get(nome));
    }

    public Task<Produto> GetProduto(int id) 
    {
        return Task.FromResult(Produtos.Get(id));
    }
       
    public Task<IEnumerable<Produto>> GetProdutosFeira(string nomeFeira)
    {
        return Task.FromResult(Produtos.GetProdutosFeira(nomeFeira));
    }

    public Task<IEnumerable<Produto>> GetProdutosVendedor(int nifVendedor)
    {
        return Task.FromResult(Produtos.GetProdutosVendedor(nifVendedor));
    }

    public Task<IEnumerable<Produto>> GetProdutosFavoritos(int nifCliente)
    {
        return Task.FromResult(Produtos.GetFavs(nifCliente));
    }

    public Task<int> GetAvaliacaoMediaProduto(int idProduto)
    {
        return Task.FromResult(Produtos.GetAvaliacaoMediaProduto(idProduto));
    }

    public void AvaliarProduto(int nifCliente, int idProduto, int valorAval)
    {
        this.Produtos.InsertAvaliacao(nifCliente, idProduto, valorAval);
        this.Produtos.UpdateAvaliacaoProduto(idProduto);
    }

    public Produto AddProduto(Produto p)
    {
        return Produtos.Insert(p);
    }

    public void AddFeira(Feira f)
    {
        try
        {
            Feiras.Insert(f);
        }
        catch (AlreadyExistsException)
        {
            throw;
        }
            
    }

    public void AddRegistoFeira(String nomeFeira, int nifVendedor)
    {
        try
        {
            Feiras.AddRegistoFeira(nomeFeira, nifVendedor);
        }
        catch (AlreadyExistsException)
        {
            throw;
        }
    }

    public Task<IEnumerable<(string produto, DateTime timestamp, float valorVenda, int quantidade, int nifCliente)>> HistoricoVendas(int nifVendedor)
    {
        IEnumerable<Produto> produtos = Produtos.GetProdutosVendedor(nifVendedor);
        IEnumerable<(string produto, DateTime timestamp, float valorVenda, int quantidade, int nifCliente)> historico = new List<(string produto, DateTime timestamp, float valorVenda, int quantidade, int nifCliente)>();

        foreach(Produto produto in produtos)
        {
            int idProduto = produto.idProduto;

            IEnumerable<(DateTime timestamp, float valorVenda, int quantidade, int nifCliente)> compras = Produtos.GetComprasProduto(idProduto);

            foreach(var compra in compras)
            {
                historico = historico.Append((produto.nome, compra.Item1, compra.Item2, compra.Item3, compra.Item4));
            }
        }

        return Task.FromResult(historico);
    }
}

