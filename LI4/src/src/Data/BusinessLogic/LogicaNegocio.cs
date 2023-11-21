using System;
using src.Data.BusinessLogic.SubCompras;
using src.Data.BusinessLogic.SubFeiras;
using src.Data.BusinessLogic.SubUsers;

namespace src.Data.BusinessLogic;

public class LogicaNegocio : ILogicaNegocio
{
    private SubComprasFacade ComprasFacade;
    private SubFeirasFacade FeirasFacade;
    private SubUtilizadoresFacade UtilizadoresFacade;
    public LogicaNegocio()
    {
        ComprasFacade = new SubComprasFacade();
        FeirasFacade = new SubFeirasFacade();
        UtilizadoresFacade = new SubUtilizadoresFacade();
    }

    public void FinalizarCompra(int nifCliente, string nomeFaturacao, string morada, string telemovel)
    {
        try
        {
            ComprasFacade.FinalizarCompra(nifCliente, nomeFaturacao, morada, telemovel);
        }
        catch (Exception)
        {
            throw;
        }
    }

    public Task<IEnumerable<(Produto, float, int)>> GetCarrinho(int nifCliente)
    {
        return ComprasFacade.GetCarrinho(nifCliente);
    }

    public void AdicionarAoCarrinho(int nifCliente, int idProduto, float valorVenda, int quantidade)
    {
        ComprasFacade.AdicionarAoCarrinho(nifCliente, idProduto, valorVenda, quantidade);
    }

    public Boolean DeleteProdutoCarrinho(int nifCliente, int idProduto)
    {
        return ComprasFacade.DeleteProdutoCarrinho(nifCliente, idProduto);
    }

    public Task<IEnumerable<Feira>> GetFeiras()
    {
        return FeirasFacade.GetFeiras();
    }

    public Task<Feira> GetFeira(string nome)
    {
        return FeirasFacade.GetFeira(nome);
    }

    public Task<Produto> GetProduto(int id)
    {
        return FeirasFacade.GetProduto(id);
    }

    public Task<IEnumerable<Produto>> GetProdutosFeira(string nomeFeira)
    {
        return FeirasFacade.GetProdutosFeira(nomeFeira);
    }

    public Task<IEnumerable<Produto>> GetProdutosVendedor(int nifVendedor)
    {
        return FeirasFacade.GetProdutosVendedor(nifVendedor);
    }

    public Task<IEnumerable<Produto>> GetProdutosFavoritos(int nifCliente)
    {
        return FeirasFacade.GetProdutosFavoritos(nifCliente);
    }

    public Task<int> GetAvaliacaoMediaProduto(int idProduto)
    {
        return FeirasFacade.GetAvaliacaoMediaProduto(idProduto);
    }

    public void AvaliarProduto(int nifCliente, int idProduto, int valorAval)
    {
        FeirasFacade.AvaliarProduto(nifCliente, idProduto, valorAval);
    }

    public Produto AddProduto(Produto p)
    {
        return FeirasFacade.AddProduto(p);
    }

    public void AddFeira(Feira f)
    {
        try
        {
            FeirasFacade.AddFeira(f);
        }
        catch(Exception) {
            throw;
        }
    }

    public void AddRegistoFeira(string nomeFeira, int nifVendedor)
    {
        try
        {
            FeirasFacade.AddRegistoFeira(nomeFeira, nifVendedor);
        }
        catch(Exception)
        {
            throw;
        }
    }

    public Task<IEnumerable<(string produto, DateTime timestamp, float valorVenda, int quantidade, int nifCliente)>> HistoricoVendas(int nifVendedor)
    {
        return FeirasFacade.HistoricoVendas(nifVendedor);
    }

    public Task<IEnumerable<Cliente>> GetClientes()
    {
        return UtilizadoresFacade.GetClientes();
    }

    public Task<IEnumerable<Vendedor>> GetVendedores()
    {
        return UtilizadoresFacade.GetVendedores();
    }

    public Task<Cliente> GetCliente(int nifCliente)
    {
        return UtilizadoresFacade.GetCliente(nifCliente);
    }

    public Task<Vendedor> GetVendedor(int nifVendedor)
    {
        return UtilizadoresFacade.GetVendedor(nifVendedor);
    }

    public Task<int> GetAvaliacao(int nifCliente, int idProduto)
    {
        return UtilizadoresFacade.GetAvaliacao(nifCliente, idProduto);
    }


    public void RegistarCliente(string nome, string email, string password, int nifCliente)
    {
        try
        {
            UtilizadoresFacade.RegistarCliente(nome, email, password, nifCliente);
        }
        catch(Exception)
        {
            throw;
        }
    }

    public void RegistarVendedor(string nome, string email, string password, int nifCliente)
    {
        try
        {
            UtilizadoresFacade.RegistarVendedor(nome, email, password, nifCliente);
        }
        catch(Exception)
        {
            throw;
        }
    }

    public Task<int> Autenticar(int nif, string password)
    {
        try
        {
            return UtilizadoresFacade.Autenticar(nif, password);
        }
        catch(Exception)
        {
            throw;
        }
    }

    public Task<(bool, bool, double, double, double)> GetContraproposta(double fAceitacao, double ftolerancia, double fresposta, double limiteSuperior, double limiteInferior, double proposta)
    {
        return ComprasFacade.GetContraproposta(fAceitacao, ftolerancia, fresposta, limiteSuperior, limiteInferior, proposta); 
    }
}

