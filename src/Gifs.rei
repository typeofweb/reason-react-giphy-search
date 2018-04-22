type singleGif = {
  url: string,
  mp4: string,
  height: string,
  width: string,
};

type gifs = list(singleGif);

type gifsResponse = option(gifs);
