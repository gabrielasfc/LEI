package src.Community;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import src.Bill.Bill;
import src.SmartDevices.SmartBulb;
import src.SmartDevices.SmartDevice;
import src.SmartDevices.SmartSpeaker;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

class ProviderTest {
    Provider p;
    @BeforeEach
    void setUp() {
        this.p = new Provider("Endesa", 10, 10, "b + c * (1+t)");
    }

    @AfterEach
    void tearDown() {

    }
    @Test
    public void testFormula(){
        double consumption = 10;
        double d = p.calculateCost(consumption); // Consumo de 10 kwh
        assertEquals(d, p.getBaseValue() + consumption * (1 + p.getTax()));
    }

    @Test
    public void testAddBill(){
        Bill b = new Bill();
        this.p.addBill(b);

        Set<Bill> addedBills = new HashSet<>();
        addedBills.add(b.clone());
        Set<Bill> billsFromProvider = p.getBills();

        Iterator<Bill> it1 = addedBills.iterator();
        Iterator<Bill> it2 = billsFromProvider.iterator();

        boolean areEqual = true;

        while (it1.hasNext() && it2.hasNext()) {
            areEqual = it1.next().equals(it2.next());
        }

        areEqual = !it1.hasNext() && !it2.hasNext();
        assertTrue(areEqual);
    }
}