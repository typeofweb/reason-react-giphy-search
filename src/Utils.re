let emptyTimeoutId: Js.Global.timeoutId = [%bs.raw "0"];

let debounce2 = (fn, time) => {
  let tout: ref(Js.Global.timeoutId) = ref(emptyTimeoutId);
  (arg1, arg2) => {
    Js.Global.clearTimeout(tout^);
    tout := Js.Global.setTimeout(() => fn(arg1, arg2), time);
  };
};
