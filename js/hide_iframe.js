function hideIframe(textContainerId, iframeId, url) {
  const iframe = document.getElementById(iframeId);
  const textContainer = document.getElementById(textContainerId);

  function loadIframe() {
    console.log("clicked!");
    iframe.src = url;
    textContainer.style.display = 'none';
    iframe.removeEventListener('click', loadIframe);
  }

  function unloadIframe() {
    iframe.src = '';
    textContainer.style.display = 'block';
    iframe.addEventListener('click', loadIframe);
  }

  // iframe.addEventListener('mouseenter', loadIframe);
  // iframe.addEventListener('mouseenter', loadIframe);
  textContainer.addEventListener('click', loadIframe);
  iframe.addEventListener('mouseleave', unloadIframe);
}
