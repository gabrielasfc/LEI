package src.SmartDevices;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class SmartCameraTest {
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
    public void testCloneEquals() {
        Resolution r = new Resolution(1920, 1080);
        SmartCamera sC = new SmartCamera(r, 1000, 1);
        SmartCamera sC2 = sC.clone();
        assertTrue(sC.equals(sC2));
    }

}