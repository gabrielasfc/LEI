using src.Data.BusinessLogic.SubFeiras;

namespace src.Data.BusinessLogic.SubCompras;

public interface ISubCompras
{
    public void FinalizarCompra(int nifCliente, string nomeFaturacao, string morada, string telemovel);

    public Task<IEnumerable<(Produto, float, int)>> GetCarrinho(int nifCliente);

    public void AdicionarAoCarrinho(int nifCliente, int idProduto, float valorVenda, int quantidade);

    public Boolean DeleteProdutoCarrinho(int nifCliente, int idProduto);

    public Task<(bool, bool, double, double, double)> GetContraproposta(double fAceitacao, double ftolerancia, double fresposta, double limiteSuperior, double limiteInferior, double proposta);
}