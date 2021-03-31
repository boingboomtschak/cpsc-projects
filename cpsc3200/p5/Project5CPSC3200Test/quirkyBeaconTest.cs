using Microsoft.VisualStudio.TestPlatform.ObjectModel.Client;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Project5CPSC3200;
using System;

namespace Project5CPSC3200Test {
    [TestClass]
    public class quirkyBeaconTest {
        [TestMethod]
        public void Test_quirkyBeacon_SignalSetSeq() {
            // Arrange
            beacon bc = new quirkyBeacon();
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
        public void Test_quirkyBeacon_ChargeFns() {
            // Arrange
            beacon bc = new quirkyBeacon();
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
        public void Test_quirkyBeacon_StateFns() {
            // Arrange
            beacon bc = new quirkyBeacon();
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
