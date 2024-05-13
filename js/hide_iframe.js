function hideIframe(textContainerId, iframeId, url) {
  const iframe = document.getElementById(iframeId);
  const textContainer = document.getElementById(textContainerId);
  let timer;

  function loadIframe() {
    console.log("clicked!");
    iframe.src = url;
    textContainer.style.display = 'none';
    iframe.removeEventListener('click', loadIframe);
  }

  function unloadIframe() {
    timer = setTimeout(function() {
      iframe.src = '';
      textContainer.style.display = 'block';
      iframe.addEventListener('click', loadIframe);
    }, 2000);
  }

  function resetTimer() {
    clearTimeout(timer); // Clear previous timer
    // unloadIframe(); // Start a new timer
  }

  // iframe.addEventListener('mouseenter', loadIframe);
  // iframe.addEventListener('mouseenter', loadIframe);
  textContainer.addEventListener('click', loadIframe);
  iframe.addEventListener('mouseleave', unloadIframe);
  iframe.addEventListener('mouseenter', resetTimer); // Reset timer when mouse reenters iframe
}
