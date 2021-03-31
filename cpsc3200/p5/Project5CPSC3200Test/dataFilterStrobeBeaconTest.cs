using Microsoft.VisualStudio.TestPlatform.ObjectModel.Client;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Project5CPSC3200;
using System;

namespace Project5CPSC3200Test {
    [TestClass]
    public class dataFilterStrobeBeaconTest {
        [TestMethod]
        public void Test_dataFilterStrobeBeacon_ConstructorPrime() {
            // Arrange/Act
            dataFilterStrobeBeacon d = new dataFilterStrobeBeacon(5);
            int[] testArray = new int[1] { 5 };

            // Assert
            CollectionAssert.AreEqual(d.filter(), testArray);
        }

        [TestMethod]
        public void Test_dataFilterStrobeBeacon_ConstructorNonPrime() {
            // Arrange/Act
            dataFilterStrobeBeacon d = new dataFilterStrobeBeacon(8);
            int[] testArray = new int[1] { 2 };

            // Assert
            CollectionAssert.AreEqual(d.filter(), testArray);
        }

        [TestMethod]
        public void Test_dataFilterStrobeBeacon_DefaultConstructor() {
            // Arrange/Act
            dataFilterStrobeBeacon d = new dataFilterStrobeBeacon();
            int[] testArray = new int[1] { 2 };

            // Assert
            CollectionAssert.AreEqual(d.filter(), testArray);
        }

        [TestMethod]
        public void Test_dataFilterStrobeBeacon_GetDefaultMode() {
            // Arrange/Act
            dataFilterStrobeBeacon d = new dataFilterStrobeBeacon();

            // Assert
            Assert.IsFalse(d.getMode());
        }

        [TestMethod]
        public void Test_dataFilterStrobeBeacon_SetMode() {
            // Arrange
            dataFilterStrobeBeacon d = new dataFilterStrobeBeacon();

            // Act
            d.setMode(true);

            // Assert
            Assert.IsTrue(d.getMode());
        }

        [TestMethod]
        public void Test_dataFilterStrobeBeacon_SetPrimeWithPrime() {
            // Arrange
            dataFilterStrobeBeacon d = new dataFilterStrobeBeacon();
            int[] testArray = new int[1] { 11 };

            // Act
            d.setPrime(11);

            // Assert
            CollectionAssert.AreEqual(d.filter(), testArray);
        }

        [TestMethod]
        public void Test_dataFilterStrobeBeacon_SetPrimeWithoutPrime() {
            // Arrange
            dataFilterStrobeBeacon d = new dataFilterStrobeBeacon(17);
            int[] testArray = new int[1] { 17 };

            // Act
            d.setPrime(18);

            // Assert
            CollectionAssert.AreEqual(d.filter(), testArray);
        }

        [TestMethod]
        public void Test_dataFilterStrobeBeacon_FilterSmallMode() {
            // Arrange
            dataFilterStrobeBeacon d = new dataFilterStrobeBeacon(23);
            int[] testArray = new int[7] { 25, 14, 29, 40, 8, 59, 2 };
            int[] assertArray = new int[3] { 14, 8, 2 };

            // Act
            d.scramble(testArray); // Using scramble to set array, ignoring its output in this test
            int[] dFilter = d.filter();

            // Assert
            CollectionAssert.AreEqual(dFilter, assertArray);
        }

        [TestMethod]
        public void Test_dataFilterStrobeBeacon_FilterLargeMode() {
            // Arrange
            dataFilterStrobeBeacon d = new dataFilterStrobeBeacon(41);
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
        public void Test_dataFilterStrobeBeacon_ScrambleEvenLengthSeq() {
            // Arrange
            dataFilterStrobeBeacon d = new dataFilterStrobeBeacon();
            int[] testArray = new int[6] { 29, 14, 34, 73, 5, 9 };
            int[] assertArray = new int[6] { 14, 29, 34, 73, 5, 9 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }

        [TestMethod]
        public void Test_dataFilterStrobeBeacon_ScrambleOddLengthSeq() {
            // Arrange
            dataFilterStrobeBeacon d = new dataFilterStrobeBeacon();
            int[] testArray = new int[5] { 29, 14, 34, 73, 5 };
            int[] assertArray = new int[5] { 14, 29, 34, 73, 5 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }

        [TestMethod]
        public void Test_dataFilterStrobeBeacon_ScrambleLargeMode() {
            // Arrange
            dataFilterStrobeBeacon d = new dataFilterStrobeBeacon();
            d.setMode(true);
            int[] testArray = new int[6] { 29, 14, 34, 73, 5, 9 };
            int[] assertArray = new int[6] { 29, 14, 73, 34, 9, 5 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }
        [TestMethod]
        public void Test_dataFilterStrobeBeacon_SignalSetSeq() {
            // Arrange
            dataFilterStrobeBeacon bc = new dataFilterStrobeBeacon();
            int[] testArray = new int[] { 1, 2, 3, 4, 5 };
            int[] signalArray = new int[5];
            int[] assertArray = new int[] { 1, -2, 3, -4, 5 };

            // Act
            bc.setSeq(testArray);
            for (int i = 0; i < signalArray.Length; i++) {
                signalArray[i] = bc.signal();
            }

            // Assert
            CollectionAssert.AreEqual(signalArray, assertArray);
        }

        [TestMethod]
        public void Test_dataFilterStrobeBeacon_ChargeFns() {
            // Arrange
            dataFilterStrobeBeacon bc = new dataFilterStrobeBeacon();
            int[] testArray = new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            int[] signalArray = new int[11];
            int[] assertArray = new int[] { 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 0 };

            // Act
            bc.setSeq(testArray);
            for (int i = 0; i < signalArray.Length; i++) {
                signalArray[i] = bc.signal();
            }
            bc.recharge(5);

            // Assert
            Assert.AreEqual(bc.getCharge(), 0);
            CollectionAssert.AreEqual(signalArray, assertArray);
        }

        [TestMethod]
        public void Test_dataFilterStrobeBeacon_StateFns() {
            // Arrange
            dataFilterStrobeBeacon bc = new dataFilterStrobeBeacon();
            int[] testArray = new int[] { 1, 2, 3, 4, 5 };
            int[] signalArray = new int[5];
            int[] assertArray = new int[] { 1, 0, -2, 0, 3 };

            // Act
            bc.setSeq(testArray);
            for (int i = 0; i < signalArray.Length; i++) {
                if (i % 2 == 0) {
                    bc.turnOn();
                } else {
                    bc.turnOff();
                }
                signalArray[i] = bc.signal();
            }

            // Assert
            CollectionAssert.AreEqual(signalArray, assertArray);
        }
    }
}
