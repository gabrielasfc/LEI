package src.Community;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import src.Exceptions.NonExistantHouseException;
import src.Exceptions.NonExistantProviderException;

import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;
import java.util.function.Consumer;

import static org.junit.jupiter.api.Assertions.*;

class CommunityTest {
    Community c;
    @BeforeEach
    void setUp() {
        this.c = new Community();

        SmartHouse c = new SmartHouse();
    }

    @AfterEach
    void tearDown() {

    }

    @Test
    public void testAdvance(){
        LocalDateTime initialTime = c.getCurrentDateTime();
        this.c.advance(10);
        LocalDateTime newTime = this.c.getCurrentDateTime();
        assertTrue(newTime.minus(10, ChronoUnit.HOURS).equals(initialTime));
    }

    @Test
    public void testAddProvider(){
        Provider p = new Provider("Endesa", 10, 10, "b + c * (1+t)");
        this.c.addProvider(p);
        assertTrue(this.c.hasProvider(p));
        assertTrue(this.c.hasProvider("Endesa"));
    }

    @Test
    public void testAddHouse(){
        SmartHouse h = new SmartHouse();
        Provider p = new Provider("Endesa", 10, 10, "b + c * (1+t)");
        this.c.addProvider(p);
        try{
            this.c.addHouse(h, "Endesa");
        } catch (NonExistantProviderException e){
            System.out.println(e.getMessage());
        }
        assertTrue(this.c.hasHouse(h));
    }

}