function getTime() {
  // Get the current time
  var now = new Date();

  // Extract hours and minutes
  var hours = now.getHours();
  var minutes = now.getMinutes();

  // Pad single digit hours and minutes with leading zeros
  hours = hours < 10 ? '0' + hours : hours;
  minutes = minutes < 10 ? '0' + minutes : minutes;

  // Output the time in hh:mm format
  var currentTime = hours + ':' + minutes;

  // Print or use currentTime as needed
  document.write(currentTime);
}
