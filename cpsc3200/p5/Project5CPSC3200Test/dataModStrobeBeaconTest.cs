using Microsoft.VisualStudio.TestPlatform.ObjectModel.Client;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Project5CPSC3200;
using System;

namespace Project5CPSC3200Test {
    [TestClass]
    public class dataModStrobeBeaconTest {
        [TestMethod]
        public void Test_dataModStrobeBeacon_FilterSmallMode() {
            // Arrange
            dataModStrobeBeacon d = new dataModStrobeBeacon(13);
            int[] testArray = new int[6] { 8, 24, 30, 31, 6, 11 };
            int[] assertArray = new int[4] { 7, 1, 5, 1 };

            // Act
            d.scramble(testArray); // NOTE: All prime numbers will be replaced with '2' before updating
            int[] dFilter = d.filter();

            // Assert
            CollectionAssert.AreEqual(dFilter, assertArray);
        }

        [TestMethod]
        public void Test_dataModStrobeBeacon_FilterLargeMode() {
            // Arrange
            dataModStrobeBeacon d = new dataModStrobeBeacon(13);
            d.setMode(true);
            int[] testArray = new int[6] { 8, 24, 30, 31, 6, 11 };
            int[] assertArray = new int[2] { 25, 31 };

            // Act
            d.scramble(testArray); // NOTE: All prime numbers will be replaced with '2' before updating
            int[] dFilter = d.filter();

            // Assert
            CollectionAssert.AreEqual(dFilter, assertArray);
        }

        [TestMethod]
        public void Test_dataModStrobeBeacon_ScrambleEvenLengthSeq() {
            // Arrange
            dataModStrobeBeacon d = new dataModStrobeBeacon();
            int[] testArray = new int[6] { 8, 24, 30, 31, 6, 11 };
            int[] assertArray = new int[6] { 8, 24, 2, 30, 2, 6 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }

        [TestMethod]
        public void Test_dataModStrobeBeacon_ScrambleOddLengthSeq() {
            // Arrange
            dataModStrobeBeacon d = new dataModStrobeBeacon();
            int[] testArray = new int[7] { 8, 24, 30, 31, 6, 11, 66 };
            int[] assertArray = new int[7] { 8, 24, 2, 30, 2, 6, 66 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }

        [TestMethod]
        public void Test_dataModStrobeBeacon_ScrambleLargeMode() {
            // Arrange
            dataModStrobeBeacon d = new dataModStrobeBeacon();
            d.setMode(true);
            int[] testArray = new int[6] { 8, 24, 30, 31, 6, 11 };
            int[] assertArray = new int[6] { 24, 8, 30, 2, 6, 2 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }
        [TestMethod]
        public void Test_dataModStrobeBeacon_SignalSetSeq() {
            // Arrange
            dataModStrobeBeacon bc = new dataModStrobeBeacon();
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
        public void Test_dataModStrobeBeacon_ChargeFns() {
            // Arrange
            dataModStrobeBeacon bc = new dataModStrobeBeacon();
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
        public void Test_dataModStrobeBeacon_StateFns() {
            // Arrange
            dataModStrobeBeacon bc = new dataModStrobeBeacon();
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
