package src.SmartDevices;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

import java.beans.Transient;

public class SmartBulbTest {
    /**
     * Sets up the test fixture.
     *
     * Called before every test case method.
     */
    @BeforeEach
    public void setUp()
    {

    }

    /**
     * Tears down the test fixture.
     *
     * Called after every test case method.
     */
    @AfterEach
    public void tearDown()
    {
    }

    @Test
    public void testConstructor(){
        SmartBulb sb1 = new SmartBulb();
        assertTrue(sb1 != null);
        SmartBulb sb2 = new SmartBulb(4, true);
        assertTrue(sb2 != null);
        SmartBulb sb3 = new SmartBulb(SmartBulb.WARM, 10, 1, 4, true);
        assertTrue(sb3 != null);
        SmartBulb sb4 = new SmartBulb(sb3);
        assertTrue(sb4 != null);
    }


    @Test
    public void testCloneEquals() {
        SmartBulb s = new SmartBulb(SmartBulb.WARM, 10, 1, 15, false);
        SmartBulb sClone = s.clone();
        assertTrue(sClone.equals(s));
    }

    @Test
    public void testTurnOFF_ON() {
        SmartBulb s = new SmartBulb(SmartBulb.WARM, 10, 1, 15, false);
        s.turnOn();
        assertEquals(s.getOnState(), true);
        s.turnOff();
        assertEquals(s.getOnState(), false);
    }
}