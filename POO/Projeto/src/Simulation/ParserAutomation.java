package src.Simulation;

import src.Change.*;
import src.Community.Community;
import src.Exceptions.NonExistantHouseException;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;

public class ParserAutomation {
    private Community community;
    private String nomeFich;

    /**
     * Construtor que recebe a comunidade e o nome do ficheiro a ser lido
     * @param community Comunidade que vai ser simulada
     * @param nomeFich Nome do ficheiro que contém a simulação
     */
    public ParserAutomation(Community community, String nomeFich) {
        this.community = community;
        this.nomeFich = nomeFich;
    }

    /**
     * Faz o parse de todas as linhas do ficheiro
     */
    public void parse(){
        List<String> lines = lerFicheiro(this.nomeFich);
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH");
        LocalDateTime dateTime = LocalDateTime.parse(lines.get(0), formatter);

        // Data do início da simulação
        LocalDateTime currDate = dateTime;
        lines.remove(0);

        // Coloca todas as casas com esta hora de início de simulação
        this.community.startSimulation(currDate);

        for(String linha: lines){
            currDate = parseLine(linha); // Atualiza a data atual com a data lida a partir da linha
        }

        System.out.println(this.community.toString());
    }

    /**
     * Faz o parse da linha obtida, invocando a mensagem apropriada na comunidade
     * @param linha String recebida por parâmetro
     * @return Nova data (data lida)
     */
    private LocalDateTime parseLine(String linha){
        String[] splits = linha.split(", ");
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH");

        // Data atual é a data do primeiro campo lido
        LocalDateTime dateTime = LocalDateTime.parse(splits[0], formatter);

        // Atualiza a data na comunidade
        this.community.setCurrentDate(dateTime);


        switch(splits[1]){
            case "endOfSimulation" :
                this.community.startNewInterval();
                break;
            case "smarthouse" :
                parseSmartHouseAlteration(splits);
                break;
            case "provider" :
                parseProviderAlteration(splits);
                break;
        }

        return dateTime;
    }

    /**
     * Faz o parse de uma linha com mudança na casa, invocando a mensagem apropriada na comunidade
     * @param splits Strings que representam os campos lidos
     */
    private void parseSmartHouseAlteration(String[] splits){
        int houseId = Integer.parseInt(splits[2]);

        String alteration = splits[3];
        String location;
        int devId;

        switch(alteration){
            case "setOff":
                devId = Integer.parseInt(splits[4]);
                try {
                    this.community.addChangeToHouseNow(houseId, new TurnOffDevice(devId));
                } catch(NonExistantHouseException e){
                    System.out.println(e.getMessage());
                }
                break;
            case "setOn":
                devId = Integer.parseInt(splits[4]);
                try {
                    this.community.addChangeToHouseNow(houseId, new TurnOnDevice(devId));
                } catch(NonExistantHouseException e){
                    System.out.println(e.getMessage());
                }
                break;
            case "setAllOn":
                try{
                    this.community.addChangeToHouseNow(houseId, new TurnOnAllDevices());
                } catch (NonExistantHouseException e){
                    System.out.println(e.getMessage());
                }
                break;
            case "setAllOff":
                try{
                    this.community.addChangeToHouseNow(houseId, new TurnOffAllDevices());
                } catch (NonExistantHouseException e){
                    System.out.println(e.getMessage());
                }
                break;
            case "setAllOnLocation":
                location = splits[4];
                try{
                    this.community.addChangeToHouseNow(houseId, new TurnOnLocation(location));
                } catch (NonExistantHouseException e){
                    System.out.println(e.getMessage());
                }
                break;
            case "setAllOffLocation":
                location = splits[4];
                try{
                    this.community.addChangeToHouseNow(houseId, new TurnOffLocation(location));
                } catch (NonExistantHouseException e){
                    System.out.println(e.getMessage());
                }
                break;
            default:
                String providerName = splits[3];
                try {
                    this.community.addChangeToHouseProviderNow(houseId, providerName); // O fornecedor só devo ser conhecido dentro da comunidade
                } catch(NonExistantHouseException e){
                    System.out.println(e.getMessage());
                }
                break;
        }
    }


    /**
     * Faz o parse de uma linha com mudança no fornecedor, invocando a mensagem apropriada na comunidade
     * @param splits Strings que representam os campos lidos
     */
    private void parseProviderAlteration(String[] splits){
        String alteration = splits[2];
        String providerName;

        switch(alteration){
            case "changeTax" :
                providerName = splits[3];
                double newTax = Double.parseDouble(splits[4]);

                this.community.changeProviderStateNow(providerName, new ChangeProviderTax(newTax, providerName));
                break;
            case "changeFormula" :
                providerName = splits[3];
                String newFormula = splits[4];

                this.community.changeProviderStateNow(providerName, new ChangeProviderFormula(newFormula, providerName));
                break;
            case "changeBaseValue" :
                providerName = splits[3];
                double newBaseValue = Double.parseDouble(splits[4]);

                this.community.changeProviderStateNow(providerName, new ChangeProviderBaseValue(newBaseValue, providerName));
                break;
            default:
                break;
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
}
