package src.Bill;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import src.Bill.Bill;

import static org.junit.jupiter.api.Assertions.*;

class BillTest {
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
        Bill b = new Bill();
        Bill b2 = b.clone();
        assertTrue(b.equals(b2));
        b2.setConsumption(1);
        assertFalse(b.equals(b2));
    }
}