using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Authorization;
using Microsoft.AspNetCore.Components.Server.ProtectedBrowserStorage;
using Microsoft.AspNetCore.Components.Web;
using src.Data;
using src.Data.BusinessLogic;
using src.Data.BusinessLogic.SubCompras;
using src.Data.BusinessLogic.SubFeiras;
using src.Data.BusinessLogic.SubUsers;
using System.Runtime.CompilerServices;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddRazorPages();
builder.Services.AddServerSideBlazor();
builder.Services.AddSingleton<SubFeirasFacade>();
builder.Services.AddSingleton<SubComprasFacade>();
builder.Services.AddSingleton<SubUtilizadoresFacade>();
builder.Services.AddSingleton<LogicaNegocio>();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Error");
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}

SubFeirasFacade f = new SubFeirasFacade();
SubUtilizadoresFacade uf = new SubUtilizadoresFacade();
SubComprasFacade compras = new SubComprasFacade();

// NÃO APAGAR
//uf.RegistarCliente("cliente", "cliente@gmail.com", "example123", 12345678);
//Vendedor v = new Vendedor(223, "joao", "joao@gmail.com", "123");
//uf.RegistarVendedor("joao", "joao@gmail.com", "123", 223);
//f.AddRegistoFeira("Ponte dos Arcos Verdes", 223);
//Produto p = new Produto("couves", (float)3.45, 200, "Batatas de Qualidade", "Produtos Agrícolas", 0, (float)0.2, (float)0.2, (float)0.2, "Ponte dos Arcos Verdes", 223);
//Produto pcp = f.AddProduto(p);
//////////////////////////

app.UseHttpsRedirection();

app.UseStaticFiles();

app.UseRouting();
app.MapBlazorHub();
app.MapFallbackToPage("/_Host");

app.Run();

