using src.Data.BusinessLogic.SubFeiras;
using System;
namespace src.Data.BusinessLogic;
public interface ILogicaNegocio
{
    public void FinalizarCompra(int nifCliente, string nomeFaturacao, string morada, string telemovel);

    public Task<IEnumerable<(Produto, float, int)>> GetCarrinho(int nifCliente);

    public void AdicionarAoCarrinho(int nifCliente, int idProduto, float valorVenda, int quantidade);

    public Boolean DeleteProdutoCarrinho(int nifCliente, int idProduto);

    public Task<IEnumerable<Feira>> GetFeiras();

    public Task<Feira> GetFeira(string nome);

    public Task<Produto> GetProduto(int id);

    public Task<IEnumerable<Produto>> GetProdutosFeira(string nomeFeira);

    public Task<IEnumerable<Produto>> GetProdutosVendedor(int nifVendedor);

    public Task<IEnumerable<Produto>> GetProdutosFavoritos(int nifCliente);

    public Task<int> GetAvaliacaoMediaProduto(int idProduto);

    public Task<int> GetAvaliacao(int nifCliente, int idProduto);

    public void AvaliarProduto(int nifCliente, int idProduto, int valorAval);

    public Produto AddProduto(Produto p);

    public void AddFeira(Feira f);

    public void AddRegistoFeira(string nomeFeira, int nifVendedor);

    public Task<IEnumerable<(string produto, DateTime timestamp, float valorVenda, int quantidade, int nifCliente)>> HistoricoVendas(int nifVendedor);
    public Task<IEnumerable<Cliente>> GetClientes();

    public Task<IEnumerable<Vendedor>> GetVendedores();

    public Task<Cliente> GetCliente(int nifCliente);

    public Task<Vendedor> GetVendedor(int nifVendedor);

    public void RegistarCliente(String nome, String email, String password, int nifCliente);

    public void RegistarVendedor(String nome, String email, String password, int nifCliente);

    public Task<int> Autenticar(int nif, String password);

    public Task<(bool, bool, double, double, double)> GetContraproposta(double fAceitacao, double ftolerancia, double fresposta, double limiteSuperior, double limiteInferior, double proposta);
}


