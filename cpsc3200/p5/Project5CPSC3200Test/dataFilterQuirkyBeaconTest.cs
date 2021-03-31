using Microsoft.VisualStudio.TestPlatform.ObjectModel.Client;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Project5CPSC3200;
using System;

namespace Project5CPSC3200Test {
    [TestClass]
    public class dataFilterQuirkyBeaconTest {
        [TestMethod]
        public void Test_dataFilterQuirkyBeacon_ConstructorPrime() {
            // Arrange/Act
            dataFilterQuirkyBeacon d = new dataFilterQuirkyBeacon(5);
            int[] testArray = new int[1] { 5 };

            // Assert
            CollectionAssert.AreEqual(d.filter(), testArray);
        }

        [TestMethod]
        public void Test_dataFilterQuirkyBeacon_ConstructorNonPrime() {
            // Arrange/Act
            dataFilterQuirkyBeacon d = new dataFilterQuirkyBeacon(8);
            int[] testArray = new int[1] { 2 };

            // Assert
            CollectionAssert.AreEqual(d.filter(), testArray);
        }

        [TestMethod]
        public void Test_dataFilterQuirkyBeacon_DefaultConstructor() {
            // Arrange/Act
            dataFilterQuirkyBeacon d = new dataFilterQuirkyBeacon();
            int[] testArray = new int[1] { 2 };

            // Assert
            CollectionAssert.AreEqual(d.filter(), testArray);
        }

        [TestMethod]
        public void Test_dataFilterQuirkyBeacon_GetDefaultMode() {
            // Arrange/Act
            dataFilterQuirkyBeacon d = new dataFilterQuirkyBeacon();

            // Assert
            Assert.IsFalse(d.getMode());
        }

        [TestMethod]
        public void Test_dataFilterQuirkyBeacon_SetMode() {
            // Arrange
            dataFilterQuirkyBeacon d = new dataFilterQuirkyBeacon();

            // Act
            d.setMode(true);

            // Assert
            Assert.IsTrue(d.getMode());
        }

        [TestMethod]
        public void Test_dataFilterQuirkyBeacon_SetPrimeWithPrime() {
            // Arrange
            dataFilterQuirkyBeacon d = new dataFilterQuirkyBeacon();
            int[] testArray = new int[1] { 11 };

            // Act
            d.setPrime(11);

            // Assert
            CollectionAssert.AreEqual(d.filter(), testArray);
        }

        [TestMethod]
        public void Test_dataFilterQuirkyBeacon_SetPrimeWithoutPrime() {
            // Arrange
            dataFilterQuirkyBeacon d = new dataFilterQuirkyBeacon(17);
            int[] testArray = new int[1] { 17 };

            // Act
            d.setPrime(18);

            // Assert
            CollectionAssert.AreEqual(d.filter(), testArray);
        }

        [TestMethod]
        public void Test_dataFilterQuirkyBeacon_FilterSmallMode() {
            // Arrange
            dataFilterQuirkyBeacon d = new dataFilterQuirkyBeacon(23);
            int[] testArray = new int[7] { 25, 14, 29, 40, 8, 59, 2 };
            int[] assertArray = new int[3] { 14, 8, 2 };

            // Act
            d.scramble(testArray); // Using scramble to set array, ignoring its output in this test
            int[] dFilter = d.filter();

            // Assert
            CollectionAssert.AreEqual(dFilter, assertArray);
        }

        [TestMethod]
        public void Test_dataFilterQuirkyBeacon_FilterLargeMode() {
            // Arrange
            dataFilterQuirkyBeacon d = new dataFilterQuirkyBeacon(41);
            d.setMode(true);
            int[] testArray = new int[7] { 59, 24, 37, 15, 63, 104, 2 };
            int[] assertArray = new int[3] { 59, 63, 104 };

            // Act
            d.scramble(testArray);
            int[] dFilter = d.filter();

            // Assert
            CollectionAssert.AreEqual(dFilter, assertArray);
        }

        [TestMethod]
        public void Test_dataFilterQuirkyBeacon_ScrambleEvenLengthSeq() {
            // Arrange
            dataFilterQuirkyBeacon d = new dataFilterQuirkyBeacon();
            int[] testArray = new int[6] { 29, 14, 34, 73, 5, 9 };
            int[] assertArray = new int[6] { 14, 29, 34, 73, 5, 9 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }

        [TestMethod]
        public void Test_dataFilterQuirkyBeacon_ScrambleOddLengthSeq() {
            // Arrange
            dataFilterQuirkyBeacon d = new dataFilterQuirkyBeacon();
            int[] testArray = new int[5] { 29, 14, 34, 73, 5 };
            int[] assertArray = new int[5] { 14, 29, 34, 73, 5 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }

        [TestMethod]
        public void Test_dataFilterQuirkyBeacon_ScrambleLargeMode() {
            // Arrange
            dataFilterQuirkyBeacon d = new dataFilterQuirkyBeacon();
            d.setMode(true);
            int[] testArray = new int[6] { 29, 14, 34, 73, 5, 9 };
            int[] assertArray = new int[6] { 29, 14, 73, 34, 9, 5 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }
        [TestMethod]
        public void Test_dataFilterQuirkyBeacon_SignalSetSeq() {
            // Arrange
            dataFilterQuirkyBeacon bc = new dataFilterQuirkyBeacon();
            int[] testArray = new int[] { 1, 2, 3, 4, 5 };
            int[] signalArray = new int[5];

            // Act
            bc.setSeq(testArray);
            for (int i = 0; i < signalArray.Length; i++) {
                signalArray[i] = bc.signal();
            }

            // Assert
            CollectionAssert.DoesNotContain(signalArray, 0);
        }

        [TestMethod]
        public void Test_dataFilterQuirkyBeacon_ChargeFns() {
            // Arrange
            dataFilterQuirkyBeacon bc = new dataFilterQuirkyBeacon();
            int[] testArray = new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            int[] signalArray = new int[11];
            int[] signalArrayValid = new int[10];

            // Act
            bc.setSeq(testArray);
            for (int i = 0; i < signalArray.Length; i++) {
                signalArray[i] = bc.signal();
            }
            for (int i = 0; i < signalArrayValid.Length; i++) {
                signalArrayValid[i] = signalArray[i];
            }
            bc.recharge(5);

            // Assert
            Assert.AreEqual(bc.getCharge(), 5);
            Assert.AreEqual(signalArray[10], 0);
            CollectionAssert.DoesNotContain(signalArrayValid, 0);
        }

        [TestMethod]
        public void Test_dataFilterQuirkyBeacon_StateFns() {
            // Arrange
            dataFilterQuirkyBeacon bc = new dataFilterQuirkyBeacon();
            int[] testArray = new int[] { 1, 2, 3, 4 };
            int[] signalArrayValid = new int[4];
            int[] signalArrayInvalid = new int[4];

            // Act
            bc.setSeq(testArray);
            for (int i = 0; i < signalArrayValid.Length; i++) {
                signalArrayValid[i] = bc.signal();
            }
            for (int i = 0; i < 4; i++) {
                bc.turnOn();
            }
            for (int i = 0; i < signalArrayInvalid.Length; i++) {
                signalArrayInvalid[i] = bc.signal();
            }

            // Assert
            CollectionAssert.DoesNotContain(signalArrayValid, 0);
        }
    }
}
