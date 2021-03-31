using System;

namespace Project1CPSC3200
{
    class P1
    {
        static void Main(string[] args)
        {
            Console.WriteLine("---- CPSC3200 P1 ----");
            Console.WriteLine("--- By Devon McKee --");
            Console.WriteLine("Unit Testing: ");
            Console.WriteLine("Constructor Tests Passed: " + testConstructor() + "\n");
            Console.WriteLine("Primes Tests Passed: " + testPrimes() + "\n");
            Console.WriteLine("Jump Tests Passed: " + testJump() + "\n");
            Console.WriteLine("Active Tests Passed: " + testActive() + "\n");
            Console.WriteLine("Reset/Revive Tests Passed: " + testResetRevive() + "\n");
        }

        static bool testConstructor() {
            // Create object with valid number
            jumpPrime j = new jumpPrime(1424);
            if (j.up() != 1427) {
                return false;
            }
            testMsg("Valid constructor test passed!");

            // Create object with invalid number
            jumpPrime j2 = new jumpPrime(5);
            if (j2.up() != 0) {
                return false;
            }

            testMsg("Invalid constructor test passed!");

            // Creating objects with random numbers
            Random rnd = new Random();
            try {
                for (int i = 0; i < 10; i++) {
                    jumpPrime j3 = new jumpPrime(rnd.Next(0, 100000));
                    j3.up();
                    j3.down();
                }
            } catch (Exception e) {
                Console.WriteLine(e);
                return false;
            }

            testMsg("Random constructor test passed!");

            // If no tests fail, return true
            return true;
        }

        static bool testPrimes() {
            // Test up() and down() against known numbers
            jumpPrime j = new jumpPrime(2134);
            if (j.up() != 2137 || j.down() != 2131) {
                return false;
            }

            jumpPrime j2 = new jumpPrime(1000);
            if (j2.up() != 1009 || j2.down() != 997) {
                return false;
            }

            jumpPrime j3 = new jumpPrime(8183);
            if (j3.up() != 8191 || j3.down() != 8179) {
                return false;
            }

            jumpPrime j4 = new jumpPrime(10000);
            if (j4.up() != 10007 || j4.down() != 9973) {
                return false;
            }

            testMsg("Known primes test passed!");

            // If no tests fail, return true
            return true;
        }

        static bool testJump() {
            // Trigger jump, check predicted jump
            jumpPrime j = new jumpPrime(7101);
            for (int i = 0; i < 24; i++) { j.up(); }
            if (j.up() != 7109 || j.down() != 7103) {
                return false;
            }

            testMsg("Predicted jump test passed!");

            // Check jump when num is already prime
            jumpPrime j2 = new jumpPrime(4999);
            for (int i = 0; i < 4; i++) { j2.up(); }
            if (j2.up() != 5003 || j2.down() != 4999) {
                return false;
            }

            testMsg("Prime jump test passed!");

            // Jumping until inactive
            jumpPrime j3 = new jumpPrime(1123);
            for (int i = 0; i < 60; i++) { j3.up(); }
            if (j3.up() != 0 && j3.down() != 0) {
                return false;
            }

            testMsg("Jump to inactive test passed!");

            // If no tests fail, return true
            return true;
        }

        static bool testActive() {
            // Object created (should be active)
            jumpPrime j = new jumpPrime(4999);
            if(!j.isActive()) {
                return false;
            }

            testMsg("Active constructor test passed!");

            // Object created with invalid number (should be inactive)
            jumpPrime j2 = new jumpPrime(5);
            if(j2.isActive()) {
                return false;
            }

            testMsg("Inactive constructor test passed!");

            // Creating and jumping until inactive
            jumpPrime j3 = new jumpPrime(1607);
            for (int i = 0; i < 20; i++) { j3.up(); }
            if(j3.isActive()) {
                return false;
            }

            testMsg("Jump to inactive isActive test passed!");

            // If no tests fail, return true
            return true;
        }

        static bool testResetRevive() {
            // Causing jump and then testing reset()
            jumpPrime j = new jumpPrime(2354);
            if (j.up() != 2357 || j.down() != 2351) {
                return false;
            }
            for (int i = 0; i < 4; i++) { j.up();  }
            if (j.up() != 2371 || j.down() != 2357) {
                return false;
            }
            j.reset();
            if (j.up() != 2357 || j.down() != 2351) {
                return false;
            }

            testMsg("Jump and reset test passed!");

            // Creating invalid jumpPrime (made inactive immediately) and attempting to revive
            jumpPrime j2 = new jumpPrime(5);
            j2.revive();
            if(j2.isActive()) {
                return false;
            }

            testMsg("Invalid revive test passed!");

            // Creating valid jumpPrime and then causing it to be inactive, then reviving
            jumpPrime j3 = new jumpPrime(1787);
            for (int i = 0; i < 20; i++) { j3.up(); }
            if (j3.isActive()) {
                return false;
            }
            j3.revive();
            if (!j3.isActive()) {
                return false;
            }

            testMsg("Valid to inactive revive test passed!");

            // Reviving active jumpPrime, causing it to be permanently disabled
            jumpPrime j4 = new jumpPrime(2284);
            if (!j4.isActive()) {
                return false;
            }
            j4.revive();
            if (j4.isActive()) {
                return false;
            }

            testMsg("Active object revive test passed!");

            // If no tests fail, return true
            return true;
        }

        static void testMsg(string msg) {
            Console.WriteLine("TEST: " + msg);
        }
    }
}
