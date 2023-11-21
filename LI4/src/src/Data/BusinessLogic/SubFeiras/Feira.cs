using System;
using Dapper.Contrib.Extensions;
using src.Data.Data;

namespace src.Data.BusinessLogic.SubFeiras;

[Table("Feira")]
public class Feira
{
    [ExplicitKey]
    public string nomeFeira { get; set; }
    public string tema { get; set; }
    public string descricao { get; set; }
    public string localFeira { get; set; }

    public Feira(string nome, string tema, string descricao, string local)
    {
        this.nomeFeira = nome;
        this.tema = tema;
        this.descricao = descricao;
        this.localFeira = local;
    }

    public Feira() { }

    public override bool Equals(object? obj)
    {
        return obj is Feira feira &&
               nomeFeira.Equals(feira.nomeFeira) &&
               tema.Equals(feira.tema) &&
               descricao.Equals(feira.descricao) &&
               localFeira.Equals(feira.localFeira);
    }

    public override string ToString()
    {
        return this.nomeFeira + ", " + this.tema + ", " + this.localFeira + ", " + this.descricao;
    }

}


