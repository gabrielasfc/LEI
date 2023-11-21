using src.Data.Data;
using src.Data.BusinessLogic.SubFeiras;
namespace src.Data.BusinessLogic.SubCompras;

public class SubComprasFacade : ISubCompras
{
    private ComprasDAO Compras;
    
    public SubComprasFacade()
    {
        this.Compras = ComprasDAO.getInstance();
    } 


    public void FinalizarCompra(int nifCliente, string nomeFaturacao, string morada, string telemovel)
    {
        IEnumerable<(Produto, float, int)> produtos = this.Compras.GetProdutosCarrinho(nifCliente);

        float valorTotal = 0;
        foreach ((Produto, float, int) t in produtos)
        {
            valorTotal += t.Item2*t.Item3;
        }

        Compra compra = new Compra(nomeFaturacao, morada, telemovel, valorTotal, DateTime.Now, nifCliente);

        try
        {
            this.Compras.FinalizarCompra(nifCliente, produtos, compra);
        }
        catch (Exception) 
        {
            throw;
        }
    }

    public Task<IEnumerable<(Produto, float, int)>> GetCarrinho(int nifCliente)
    {
        foreach((Produto, float, int) t in this.Compras.GetProdutosCarrinho(nifCliente))
        {
            Console.WriteLine(t.Item1.descricao);
        }

        return Task.FromResult(this.Compras.GetProdutosCarrinho(nifCliente));
    }

    public void AdicionarAoCarrinho(int nifCliente, int idProduto, float valorVenda, int quantidade)
    {
        this.Compras.InsertProdutoCarrinho(nifCliente, idProduto, valorVenda, quantidade);
    }

    public Boolean DeleteProdutoCarrinho(int nifCliente, int idProduto)
    {
        return this.Compras.DeleteProdutoCarrinho(nifCliente, idProduto);
    }

    public Task<(bool,bool,double,double,double)> GetContraproposta(double fAceitacao, double ftolerancia, double fresposta, double limiteSuperior, double limiteInferior, double proposta)
    {
        double ta = Math.Round(limiteSuperior - limiteSuperior * fAceitacao,2);
        bool aceitou = false;
        bool continua = true;
        double valorResposta = 0;

        if (proposta >= ta)
        {
            aceitou = true;
            valorResposta = proposta;
        }
        else if (proposta < limiteInferior)
        {
            continua = false;
        }
        else
        {
            limiteSuperior = Math.Round(limiteSuperior - (limiteSuperior - limiteInferior) * fresposta, 2);
            limiteInferior = Math.Round(limiteInferior + (limiteSuperior - limiteInferior) * fresposta, 2);
            if (proposta>limiteInferior)
            {
                limiteInferior = proposta;
            }
        }

        return Task.FromResult((continua, aceitou, valorResposta, limiteSuperior, limiteInferior));
    }


}