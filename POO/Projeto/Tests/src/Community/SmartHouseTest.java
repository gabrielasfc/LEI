package src.Community;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import src.Change.Change;
import src.Change.TurnOnAllDevices;
import src.Change.TurnOnDevice;
import src.Change.TurnOnLocation;
import src.SmartDevices.SmartBulb;
import src.SmartDevices.SmartDevice;
import src.SmartDevices.SmartSpeaker;

import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.*;

class SmartHouseTest {
    SmartHouse sH;

    @BeforeEach
    void setUp() {

    }

    @AfterEach
    void tearDown() {
    }

    @Test
    public void addDevice(){
        SmartDevice d1 = new SmartBulb();
        this.sH.addDevice(d1, "Sala");

        assertTrue(this.sH.hasDevice(d1.getId()));
    }

    @Test
    public void testApplyChanges1() throws Exception {}{
        this.sH = new SmartHouse("Trav Dr Vaz Guedes", "Miguel de Sousa Braga", 268388601, "Endesa");
        SmartDevice d1 = new SmartBulb(1, 10, 10);

        d1.turnOn();
        double consumption = d1.getConsumption();
        d1.turnOff();

        this.sH.startSimulation(LocalDateTime.now());
        this.sH.addDevice(d1, "Cozinha");

        Change c1 = new TurnOnDevice(d1.getId());
        this.sH.addChange(c1, LocalDateTime.now());

        assertEquals(sH.getCurrentConsumption(), consumption);
    }

    @Test
    public void testApplyChanges2() throws Exception {}{
        this.sH = new SmartHouse("Trav Dr Vaz Guedes", "Miguel de Sousa Braga", 268388601, "Endesa");

        SmartDevice d1 = new SmartBulb(1, 10, 10);

        d1.turnOn();
        double consumption = d1.getConsumption();
        d1.turnOff();

        SmartDevice d2 = new SmartBulb(1, 10, 10);

        d2.turnOn();
        consumption += d2.getConsumption();
        d2.turnOff();

        this.sH.startSimulation(LocalDateTime.now());
        this.sH.addDevice(d1, "Cozinha");
        this.sH.addDevice(d2, "Cozinha");

        Change c1 = new TurnOnLocation("Cozinha");
        this.sH.addChange(c1, LocalDateTime.now());
        assertEquals(sH.getCurrentConsumption(), consumption);
    }
}