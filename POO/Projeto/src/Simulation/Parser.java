package src.Simulation;

import src.Community.Community;
import src.Community.Provider;
import src.Exceptions.NonExistantProviderException;
import src.SmartDevices.*;
import src.Community.SmartHouse;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.nio.file.Files;
import java.util.Map;

public class Parser {
    private Community community; // Método de agregação
    private String currProvider; // Variável auxiliar - necessária para o método que faz parse da casa


    /**
     * Construtor vazio que cria a comunidade
     */
    public Parser(){
        this.community = new Community();
    }

    /**
     * Devolve a comunidade
     * @return Referência para a comundade
     */
    public Community getCommunity(){
        return this.community; // Não fazemos clone porque queremos manter as referências dos fornecedores nas casas a que eles pertencem
    }

    // Não temos setter porque a comunidade é sempre criada a partir do parser

    /**
     * Função que faz o parse do ficheiro
     * @param fileName Nome do ficheiro
     */
    public void parse(String fileName){
        List<String> linhas = lerFicheiro(fileName);
        String[] linhaPartida;
        String divisao = null;
        SmartHouse casaMaisRecente = null;
        String providerHouse = null;
        for (String linha : linhas) {
            linhaPartida = linha.split(":", 2);
            switch(linhaPartida[0]){
                case "Casa":
                    if (casaMaisRecente != null){
                        try{
                            this.community.addHouse(casaMaisRecente, this.currProvider);
                        } catch(NonExistantProviderException e){
                            System.out.println(e.getMessage());
                        }
                    }
                    casaMaisRecente = parseCasa(linhaPartida[1]);
                    break;
                case "Divisao":
                    if (casaMaisRecente == null) System.out.println("Linha inválida.");
                    divisao = linhaPartida[1];
                    break;
                case "SmartBulb":
                    if (divisao == null) System.out.println("Linha inválida.");
                    SmartBulb sd = parseSmartBulb(linhaPartida[1]);
                    casaMaisRecente.addDevice(sd, divisao);
                    break;
                case "SmartCamera":
                    if (divisao == null) System.out.println("Linha inválida.");
                    SmartCamera sc = parseSmartCamera(linhaPartida[1]);
                    casaMaisRecente.addDevice(sc, divisao);
                    break;
                case "SmartSpeaker":
                    if (divisao == null) System.out.println("Linha inválida.");
                    SmartSpeaker ss = parseSmartSpeaker(linhaPartida[1]);
                    casaMaisRecente.addDevice(ss, divisao);
                    break;
                case "Fornecedor":
                    Provider p = parseProvider(linhaPartida[1]);
                    this.community.addProvider(p);
                    break;
                default:
                    System.out.println("Linha inválida.");
                    break;
            }
        }
    }

    /**
     * Lê o ficheiro, dividindo-o por linhas
     * @param nomeFich Nome do ficheiro a ler
     * @return Lista com as linhas lidas
     */
    private List<String> lerFicheiro(String nomeFich) {
        List<String> lines;
        try { lines = Files.readAllLines(Paths.get(nomeFich), StandardCharsets.UTF_8); }
        catch(IOException exc) { lines = new ArrayList<>(); }
        return lines;
    }

    /**
     * Faz parse de uma casa
     * @param input String com o input da casa
     * @return A casa criada
     */
    private SmartHouse parseCasa(String input){
        String[] campos = input.split(",");
        String nome = campos[0];
        int nif = Integer.parseInt(campos[1]);
        String providerName = campos[2];

        SmartHouse c = new SmartHouse(nome, nif);
        this.currProvider = providerName;

        return c;
    }

    /**
     * Faz parse de uma lâmpada
     * @param input String com o input
     * @return A SmartBulb criada
     */
    private SmartBulb parseSmartBulb(String input){
        String[] campos = input.split(",");
        int tone = parseTone(campos[0]);
        int dimension = Integer.parseInt(campos[1]);
        double consumption = Double.parseDouble(campos[2]) / 24;

        SmartBulb s = new SmartBulb(tone, dimension, consumption);
        return s;
    }

    /**
     * Faz parse do tone da lâmpada
     * @param input String com o input
     * @return Inteiro com o tone da lâmpada (0 - Cold, 1 - Neutral, 2 - Warm)
     */
    private int parseTone(String input){
        int tone = 0;

        switch(input){
            case "Warm":
                tone = 2;
                break;
            case "Neutral":
                tone = 1;
                break;
            case "Cold":
                tone = 0;
                break;
        }
        return tone;
    }

    /**
     * Faz parse de uma câmara
     * @param input String com o input
     * @return A SmartCamera criada
     */
    private SmartCamera parseSmartCamera(String input){
        String[] campos = input.split(",");

        Resolution r = parseResolution(campos[0]);
        int fileSize = Integer.parseInt(campos[1]);
        double consumption = Double.parseDouble(campos[2]) / 24;

        SmartCamera s = new SmartCamera(r, fileSize, consumption);

        return s;
    }

    /**
     * Faz parse da resolução de uma câmara
     * @param input String com o input
     * @return Resolução lida
     */
    private Resolution parseResolution(String input){
        int dimX, dimY;
        String[] dims = input.substring(1).split("x");
        dimX = Integer.parseInt(dims[0]);
        dimY = Integer.parseInt(dims[1].substring(0, dims[1].length() - 1));

        Resolution r = new Resolution(dimX, dimY);
        return r;
    }

    /**
     * Faz parse da coluna
     * @param input String com o input
     * @return A SmartSpeaker criada
     */
    private SmartSpeaker parseSmartSpeaker(String input){
        String[] campos = input.split(",");

        int volume = Integer.parseInt(campos[0]);
        String station = campos[1];
        String brand = campos[2];
        double consumption = Double.parseDouble(campos[3]) / 24; // Kwh / h

        SmartSpeaker s = new SmartSpeaker(volume, station, brand, consumption);
        return s;
    }

    /**
     * Faz parse do fornecedor
     * @param input String com o input
     * @return O Provider criado
     */
    private Provider parseProvider(String input){
        String[] campos = input.split(",");

        String nome = campos[0];
        String formula = campos[1];

        Provider p = new Provider(nome, formula);
        return p;
    }
}
