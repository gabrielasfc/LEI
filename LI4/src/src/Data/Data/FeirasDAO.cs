using System;
using Dapper;
using Dapper.Contrib;
using Dapper.Contrib.Extensions;
using Microsoft.Data.SqlClient;
using Microsoft.VisualBasic;
using src.Data.BusinessLogic.SubFeiras;
using src.Data.BusinessLogic.Excecoes;

namespace src.Data.Data;

public class FeirasDAO
{   

    private static FeirasDAO singleton = null;
    private FeirasDAO()
    {
    }

    public static FeirasDAO GetInstance()
    {
        if (singleton == null)
        {
            singleton = new FeirasDAO();
        }

        return singleton;
    }

    public Feira Get(string Nome)
    {
        const string connectionString = DAOConfig.URL;

        Feira feira;
        using (var connection = new SqlConnection(connectionString))
        {
            feira = connection.Get<Feira>(Nome);
        }

        return feira;
    }

    public Feira Insert(Feira f)
    {
        const string connectionString = DAOConfig.URL;
        
        using (var connection = new SqlConnection(connectionString))
        {
            try {
                connection.Insert<Feira>(f);
            }
            catch(Exception) {
                throw new AlreadyExistsException("Feira já existente.");
            }
                
        }
               
        return f;
    }

    public Feira Delete(string key)
    {
        const string connectionString = DAOConfig.URL;

        Feira f = Get(key);

        using (var connection = new SqlConnection(connectionString))
        {
            bool b = connection.Delete<Feira>(f);
            Console.WriteLine(b);
        }

        return f;
    }

 

    public IEnumerable<Feira> GetAll()
    {
        const string connectionString = DAOConfig.URL;
        IEnumerable<Feira> feiras;

        using (var connection = new SqlConnection(connectionString))
        {
            feiras = connection.GetAll<Feira>();
        }

        return feiras;
    }


    public void AddRegistoFeira(String nomeFeira, int nifVendedor)
    {
        const string connectionString = DAOConfig.URL;

        using (var connection = new SqlConnection(connectionString))
        {
            try
            {
                var parameters = new { NomeFeira = nomeFeira, NIFVendedor = nifVendedor };
                connection.Execute("INSERT INTO RegistoFeira VALUES (@NomeFeira, @NIFVendedor)", parameters);
            }
            catch (Exception) {
                throw new AlreadyExistsException("Registo na feira já efetuado anteriormente.");
            }
        }

    }

}
