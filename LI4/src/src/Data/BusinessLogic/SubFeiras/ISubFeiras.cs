using System;
using System.Collections;

namespace src.Data.BusinessLogic.SubFeiras;

public interface ISubFeiras
{
    public Task<IEnumerable<Feira>> GetFeiras();

    public Task<Feira> GetFeira(string nome);

    public Task<Produto> GetProduto(int id);

    public Task<IEnumerable<Produto>> GetProdutosFeira(string nomeFeira);

    public Task<IEnumerable<Produto>> GetProdutosVendedor(int nifVendedor);

    public Task<IEnumerable<Produto>> GetProdutosFavoritos(int nifCliente);

    public Task<int> GetAvaliacaoMediaProduto(int idProduto);

    public void AvaliarProduto(int nifCliente, int idProduto, int valorAval);

    public Produto AddProduto(Produto p);

    public void AddFeira(Feira f);

    public void AddRegistoFeira(string nomeFeira, int nifVendedor);

    public Task<IEnumerable<(string produto, DateTime timestamp, float valorVenda, int quantidade, int nifCliente)>> HistoricoVendas(int nifVendedor);
}

