// blink request
document.getElementById('blink-led-link').onclick = async (event) => {
  event.preventDefault();

  await fetch('/blink', {
    method: 'POST',
  });
};

// switch request
const switchLedLink = document.getElementById('switch-led-link')
switchLedLink.onclick = async (event) => {
  event.preventDefault();

  const response = await fetch('/switch', {
    method: 'POST',
  });

  try {
    const { ledStatus } = JSON.parse(await response.text());

    // update button class
    const button = switchLedLink.querySelector('button');
    button.classList.remove('on', 'off');
    button.classList.add(ledStatus.toLowerCase());

    // update button text
    button.textContent = `Turn ${ledStatus === 'ON' ? 'OFF' : 'ON'}`;
  } catch (error) {
    console.error('failed to parse response', error);
    return;
  }
};

// color picker
const colorPicker = new iro.ColorPicker('#picker', {
  color: "#f00", // initial color red
});

colorPicker.on('input:end', async (color) => {
  console.log('Selected color:', color.rgb);

  await fetch('/color', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify(color.rgb),
  });
});
