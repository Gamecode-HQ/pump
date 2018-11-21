defmodule Pump.Metrics.GPUBusy do
  @moduledoc """
  /sys/class/drm/card0/device/gpu_busy_percent
  """

  def metrics() do
    gpu = case File.read("/sys/class/drm/card0/device/gpu_busy_percent") do
      {:ok, data} -> data |> String.strip |> String.to_integer
      _ -> 0
    end

    [{"gpu_busy_percent", [], gpu}]
  end
end
