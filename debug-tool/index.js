const SerialPort = require('serialport');

const port = new SerialPort('/dev/cu.SLAB_USBtoUART', { 
  baudRate: 9600,
  rtscts: false
}, (err) => {
  if (err) {
    console.log('Open Error: ', err);
  }
});

port.on('error', function(err) {
  console.log('Error: ', err.message)
})

let buff = [];
let buffPos = 0;
port.on('data', (dataBuff) => {
  console.log(dataBuff);
  // for (let i = 0; i < dataBuff.length; i++) {
  //   if (buffPos == 0 && dataBuff[i] == 0xA0) {
  //     buff[buffPos] = dataBuff[i];
  //     buffPos++;
  //   } else if (buffPos > 0 && buffPos < 9) {
  //     buff[buffPos] = dataBuff[i];
  //     buffPos++;
  //   } else if (buffPos >= 9) {
  //     process.stdout.write(buff.map(b => toHex(b)).join(' ') + '\n');
  //     buffPos = 0;
  //   }
  // }
})

process.stdin.on('data', (data) => {
  let send;
  switch (data[0]) {
    case 49: send = [0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]; break;
    case 50: send = [0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]; break;
    case 51: send = [0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]; break;
    case 52: send = [0x01, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00]; break;
    case 53: send = [0x01, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]; break;
  }
  let crc = 0;
  let iter = 0;
  let start = true;
  let a = () => {
    if (start) {
      port.write([0xA0]);
      start = false;
      setTimeout(a, 10);
      return;
    }
    if (iter >= send.length) {
      port.write([crc]);
      return;
    }
    port.write([send[iter]]);
    crc += send[iter];
    iter++;
    if (iter <= send.length) setTimeout(a, 10);
  }
  a();
})

function toHex(d) {
  return  ("0"+(Number(d).toString(16))).slice(-2).toUpperCase()
}